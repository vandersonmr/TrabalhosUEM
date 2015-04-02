%name Parser
%define LSP_NEEDED
%define MEMBERS                 \
    virtual ~Parser()   {} \
    private:                   \
       yyFlexLexer lexer;
%define LEX_BODY {return lexer.yylex();}
%define ERROR_BODY {cerr << "error encountered at line: "<<lexer.lineno()<<" last word parsed:"<<lexer.YYText()<<"\n";} 

%{
using namespace std;
#include <include/AST.hpp>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <FlexLexer.h>
extern int i;
extern int vals[3];

vector<ExprAST*> Expressions;                                                                     

llvm::LLVMContext &Context = llvm::getGlobalContext();
llvm::Module *module    = new llvm::Module("Loop JIT", Context);
llvm::IRBuilder<> Builder(Context);
%}

%token LOOP DO END ATR VAR CONST SOMA SUB PRINT

%pure_parser

%union{
  void    *Expr;
  int      num;
}

%type <Expr> P
%type <num> VAR
%type <num> CONST
%start Program

%%
Program: 
    | Program P { 
      Expressions.push_back(static_cast<ExprAST*>($2)); 
    }
P: 
 VAR ATR VAR SOMA CONST ';' {
      auto *VariableAtribution = new VariableExprAST(vals[1]);
      auto *Variable           = new VariableExprAST(vals[2]);
      auto *Number             = new NumberExprAST(vals[0]);
      VariableAtribution->SetContext(module, &Builder);
      Variable->SetContext(module, &Builder);
      Number->SetContext(module, &Builder);
      auto expr = new ArithmeticExprAST('+', VariableAtribution, Number, Variable);
      expr->SetContext(module, &Builder);
      $$ = expr;
   }
   | VAR ATR VAR SUB CONST ';' {
      auto *VariableAtribution = new VariableExprAST(vals[1]);
      auto *Variable           = new VariableExprAST(vals[2]);
      auto *Number             = new NumberExprAST(vals[0]);
      VariableAtribution->SetContext(module, &Builder);
      Variable->SetContext(module, &Builder);
      Number->SetContext(module, &Builder);
      auto expr = new ArithmeticExprAST('-', VariableAtribution, Number, Variable);
      expr->SetContext(module, &Builder);
      $$ = expr;
   } 
   | LOOP VAR DO P END ';' {
      auto *Variable = new VariableExprAST(vals[3]);
      auto *P        = (ExprAST*) $4; 
      Variable->SetContext(module, &Builder);
      auto expr = new LoopExprAST(Variable, P);
      expr->SetContext(module, &Builder);
      $$ = expr;
   }
   | PRINT VAR ';' {
      auto *Variable = new VariableExprAST(vals[3]);
      Variable->SetContext(module, &Builder); 
      auto expr = new PrintExprAST(Variable);
      expr->SetContext(module, &Builder);
      $$ = expr;
   };

%%

int main(int argc, char ** argv) {
  Parser parser;
  parser.yyparse();
  llvm::FunctionType *FuncType = 
        llvm::FunctionType::get(Builder.getVoidTy(), false);
  llvm::Function *MainFunc = 
        llvm::Function::Create(FuncType, 
                               llvm::Function::ExternalLinkage, "main", module);
  llvm::BasicBlock *Entry = llvm::BasicBlock::Create(Context, 
                                                     "entrypoint", MainFunc);
  Builder.SetInsertPoint(Entry);

  std::vector<llvm::Type*> printf_arg_types;
  printf_arg_types.push_back(llvm::Type::getInt8PtrTy(Context));
  llvm::FunctionType* printf_type =
   llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), printf_arg_types, true);
  llvm::Function *func = llvm::Function::Create(
                                  printf_type, llvm::Function::ExternalLinkage,
                                  llvm::Twine("printf"), module);
  func->setCallingConv(llvm::CallingConv::C);

  for(auto i : Expressions) {
    i->Codegen();
  }

  Builder.CreateRetVoid();
  module->dump();
  return 0;
}
