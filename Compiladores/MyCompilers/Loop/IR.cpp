#include <include/AST.hpp>
#include <stdlib.h>

llvm::Value* Variables[100];

using namespace std;

llvm::Value *NumberExprAST::Codegen() {
  return llvm::ConstantInt::get(Builder->getInt32Ty(), Val);
}

void SetVariable(int Var, llvm::Type* t, llvm::Module* module) {
  if(Variables[Var] == nullptr) {
    char buffer[33];
    sprintf(buffer, "%d", Var);
    llvm::GlobalVariable* x1 = new llvm::GlobalVariable(
                                               /*Module=*/*module, 
                                               /*Type=*/t,
                                               /*isConstant=*/false,
                                               llvm::GlobalValue::CommonLinkage,
                                               /*Initializer=*/
                                               llvm::ConstantInt::get(t, 0), 
                                               /*Name=*/buffer);
    Variables[Var] = x1;
  }
} 

llvm::Value *VariableExprAST::Codegen() {
  if(Var >= 100 || Var < 0) {
    cerr << "A variável deve estar entre X0 e X99" << endl;
    return NULL;
  } else {
    char buffer[33];
    sprintf(buffer, "%d", Var);
    SetVariable(Var, Builder->getInt32Ty(), module);
    return Builder->CreateLoad(Variables[Var], buffer);
  }
}

llvm::Value *ArithmeticExprAST::Codegen() {
  llvm::Value *VarValue = Variable->Codegen();
  llvm::Value *Const    = Number->Codegen();
  SetVariable(VariableAtribution->Var, Builder->getInt32Ty(), module);
  llvm::Value *Tmp;
  switch(Op) {
    case '+': Tmp = Builder->CreateAdd(VarValue, Const, "tmp"); break;
    case '-': Tmp = Builder->CreateSub(VarValue, Const, "tmp"); break;
    default: 
      cerr << "Operação não existe!" << endl;
      return NULL;
  }

  Builder->CreateStore(Tmp, Variables[VariableAtribution->Var]);
  return Tmp;
}

llvm::Value *LoopExprAST::Codegen() {


  llvm::Function *TheFunction   = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *PreheaderBB = Builder->GetInsertBlock();
  llvm::BasicBlock *LoopBB      = llvm::BasicBlock::Create(module->getContext(), 
                                                          "loop", TheFunction);
  Builder->CreateBr(LoopBB);
  Builder->SetInsertPoint(LoopBB);

  P->Codegen();

  auto one = llvm::ConstantInt::get(Builder->getInt32Ty(), 1);
  auto zero = llvm::ConstantInt::get(Builder->getInt32Ty(), 0);
  
  auto var = Variable->Codegen();
  auto cond = Builder->CreateICmpEQ(var, zero, "loopcond");

  auto Tmp = Builder->CreateSub(var, one, "tmp"); 
  Builder->CreateStore(Tmp, Variables[Variable->Var]);

  llvm::BasicBlock *LoopEndBB = Builder->GetInsertBlock();
  llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(module->getContext(), 
                                                      "afterloop", TheFunction);
  Builder->CreateCondBr(cond, AfterBB, LoopBB);
  Builder->SetInsertPoint(AfterBB);

  return nullptr;
}

llvm::Value *PrintExprAST::Codegen() {
  auto VariableAtribution = Variable->Codegen();
  llvm::Constant *format_const =
    llvm::ConstantDataArray::getString(module->getContext(), "%d\n");
  llvm::GlobalVariable *v =
    new llvm::GlobalVariable(
        *module, llvm::ArrayType::get(Builder->getInt8Ty(), 4),
        true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");

  llvm::Constant *zero =
   llvm::Constant::getNullValue(Builder->getInt8Ty()); 

  std::vector<llvm::Constant*> indices;
  indices.push_back(zero);
  indices.push_back(zero);
  llvm::Constant *var_ref =
    llvm::ConstantExpr::getGetElementPtr(v, indices);

  std::vector<llvm::Type*> printf_arg_types;
  printf_arg_types.push_back(Builder->getInt8PtrTy());
  llvm::FunctionType* printf_type =
    llvm::FunctionType::get(Builder->getInt32Ty(), printf_arg_types, true);

  llvm::CallInst *call = Builder->CreateCall2(
      module->getOrInsertFunction("printf", printf_type), var_ref, 
                                  VariableAtribution);
  call->setTailCall(false);

  return nullptr; 
}

