#ifndef AST_HPP
#define AST_HPP
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"                                                       
#include "llvm/IR/Module.h"
#include <iostream>

class ExprAST {
  protected:
  llvm::Value *ErrorV(const char *Str) { 
    std::cout << Str << std::endl; return 0; }
  public:
  llvm::Module *module;
  llvm::IRBuilder<>* Builder;

  void SetContext(llvm::Module* m, llvm::IRBuilder<>* b) 
                                    { module = m; 
                                      Builder = b; 
                                    };
  virtual ~ExprAST() {};
  virtual llvm::Value *Codegen() = 0;
};


class NumberExprAST : public ExprAST {
  int Val;
  public:
  NumberExprAST(int val) : Val(val) {};
  virtual llvm::Value *Codegen();
};

class VariableExprAST : public ExprAST {
  public:
  int Var;
  VariableExprAST(int var) : Var(var) {};
  virtual llvm::Value *Codegen();
};

class ArithmeticExprAST : public ExprAST {
  char Op;
  NumberExprAST   *Number;
  VariableExprAST *VariableAtribution;
  VariableExprAST *Variable;
  public:
  ArithmeticExprAST(char op, VariableExprAST *variableAtribution, 
                    NumberExprAST *number, VariableExprAST *variable) 
    : Op(op), VariableAtribution(variableAtribution),
      Number(number), Variable(variable) {};
  virtual llvm::Value *Codegen();
};

class LoopExprAST : public ExprAST {
  VariableExprAST *Variable;
  ExprAST *P;
  public:
  LoopExprAST(VariableExprAST *variable, ExprAST *p) 
    : Variable(variable), P(p) {};
  virtual llvm::Value *Codegen();
};

class PrintExprAST : public ExprAST {
  VariableExprAST *Variable;
  public:
  PrintExprAST(VariableExprAST* variable) 
    : Variable(variable) {};
  virtual llvm::Value *Codegen();
};
#endif
