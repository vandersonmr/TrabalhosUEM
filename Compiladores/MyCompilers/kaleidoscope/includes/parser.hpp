#ifndef PARSER_HPP
#define PARSER_HPP
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <scanner.hpp>

namespace {
llvm::LLVMContext &Context = llvm::getGlobalContext();
llvm::Module *TheModule = new llvm::Module("my cool jit", Context);
llvm::IRBuilder<> Builder(llvm::getGlobalContext());
std::map<std::string, llvm::Value*> NamedValues;
}
// ExprAST - Base class for all expression nodes.
class ExprAST {
  protected:
  llvm::Value *ErrorV(const char *Str) { cout << Str << endl;  return 0; }
  public:
    virtual ~ExprAST() {};
    virtual llvm::Value *Codegen() = 0;
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double Val;
  public:
  NumberExprAST(double val) : Val(val) {};
  virtual llvm::Value *Codegen();
};

// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;
  public:
  VariableExprAST(const std::string &name) : Name(name) {};
  virtual llvm::Value *Codegen();
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  ExprAST *LHS, *RHS;
  public:
  BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs)
    : Op(op), LHS(lhs), RHS(rhs) {};
  virtual llvm::Value *Codegen();
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<ExprAST*> Args;
  public:
  CallExprAST(const std::string &callee, std::vector<ExprAST*> &args)
    : Callee(callee), Args(args) {};
  virtual llvm::Value *Codegen();
};

// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;
  public:
  PrototypeAST(const std::string &name, const std::vector<std::string> &args)
    : Name(name), Args(args) {};
  virtual llvm::Function *Codegen();
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  PrototypeAST *Proto;
  ExprAST *Body;
  public:
  FunctionAST(PrototypeAST *proto, ExprAST *body)
    : Proto(proto), Body(body) {};
  virtual llvm::Function *Codegen();
};

class Parser {
  private:
    Scanner scanner;
    int CurTok;
    int getNextToken();
    std::map<char, int> BinopPrecedence; 
    ExprAST *Error(const char *Str);
    PrototypeAST *ErrorP(const char *Str); 
    FunctionAST *ErrorF(const char *Str); 
    ExprAST *ParseNumberExpr();
    ExprAST *ParseParenExpr();
    ExprAST *ParseIdentifierExpr();
    ExprAST *ParsePrimary();
    int GetTokPrecedence();
    ExprAST *ParseBinOpRHS(int,ExprAST*);
    ExprAST *ParseExpression();
    PrototypeAST *ParsePrototype();
    FunctionAST *ParseDefinition();
    FunctionAST *ParseTopLevelExpr();
    PrototypeAST *ParseExtern();

    void HandleDefinition();
    void HandleExtern();
    void HandleTopLevelExpression();
  public:
    Parser() {
      BinopPrecedence['<'] = 10;
      BinopPrecedence['+'] = 20;
      BinopPrecedence['-'] = 20;
      BinopPrecedence['*'] = 40;  
    };
    void MainLoop();
};
#endif
