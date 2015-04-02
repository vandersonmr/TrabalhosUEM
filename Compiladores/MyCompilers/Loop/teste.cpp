#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include <llvm/Support/raw_ostream.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

int main() {
  llvm::LLVMContext & context = llvm::getGlobalContext();
  llvm::Module *module = new llvm::Module("Loop", context);
  llvm::IRBuilder<> builder(context);

  llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
  llvm::Function *mainFunc = 
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);
  llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entrypoint", mainFunc);
  builder.SetInsertPoint(entry);

  llvm::GlobalVariable* x0 = new llvm::GlobalVariable(
                                                    /*Module=*/*module, 
                                                    /*Type=*/builder.getInt32Ty(),
                                                    /*isConstant=*/false,
                                                    llvm::GlobalValue::CommonLinkage,
                                                    /*Initializer=*/0, 
                                                    /*Name=*/"x0");

  llvm::GlobalVariable* x1 = new llvm::GlobalVariable(
                                                    /*Module=*/*module, 
                                                    /*Type=*/builder.getInt32Ty(),
                                                    /*isConstant=*/false,
                                                    llvm::GlobalValue::CommonLinkage,
                                                    /*Initializer=*/0, 
                                                    /*Name=*/"x1");

  llvm::ConstantInt* val1 = 
        llvm::ConstantInt::get(builder.getInt32Ty(), 1);

  llvm::Value* value = builder.CreateLoad(x0);
  value = builder.CreateAdd(value, val1);
  builder.CreateStore(value, x1);

  value = builder.CreateLoad(x1);
  value = builder.CreateAdd(value, val1);
  builder.CreateStore(value, x0);
  //llvm::Value *helloWorld = builder.CreateGlobalStringPtr("hello world!\n");

  //std::vector<llvm::Type *> putsArgs;
  //putsArgs.push_back(builder.getInt8Ty()->getPointerTo());
  //llvm::ArrayRef<llvm::Type*>  argsRef(putsArgs);

  //llvm::FunctionType *putsType = 
  //  llvm::FunctionType::get(builder.getInt32Ty(), argsRef, false);
  //llvm::Constant *putsFunc = module->getOrInsertFunction("puts", putsType);

  //builder.CreateCall(putsFunc, helloWorld);
  builder.CreateRetVoid();
  module->dump();
}
