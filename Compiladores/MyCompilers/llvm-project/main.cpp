#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Analysis/BlockFrequencyInfo.h>
#include <llvm/PassManager.h>
#include <llvm/IR/DataLayout.h>
#include "llvm/Analysis/Passes.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/GCOV.h"
#include <vector>

#include <iostream>
#include <llvm/ExecutionEngine/ExecutionEngine.h>

using namespace llvm;

std::vector<std::unique_ptr<GCOVFunction>> 
readFunctions(GCOVFile& GF, GCOVBuffer &GCNOBuffer, GCOVBuffer &GCDABuffer) {
  GCOV::GCOVVersion Version;
  std::vector<std::unique_ptr<GCOVFunction>> Functions;
  uint32_t Checksum;

  GCOVOptions options(true, true, true, true, true, true, false, false);
  FileInfo FI(options);

  if (!GCNOBuffer.readGCNOFormat() || !GCDABuffer.readGCDAFormat()) 
    return Functions;
  if (!GCNOBuffer.readGCOVVersion(Version) || 
      !GCDABuffer.readGCOVVersion(Version)) 
    return Functions;

  if (!GCNOBuffer.readInt(Checksum) || !GCDABuffer.readInt(Checksum)) 
    return Functions;
  while (true) {
    if (!GCNOBuffer.readFunctionTag()) break;
    if (!GCDABuffer.readFunctionTag()) break; 
    auto GFun = make_unique<GCOVFunction>(GF);
    if (!GFun->readGCNO(GCNOBuffer, Version) ||
        !GFun->readGCDA(GCDABuffer, Version))
      return Functions;

    GFun->collectLineCounts(FI);
    Functions.push_back(std::move(GFun));
  }
  
  FI.setRunCount(1);
  FI.setProgramCount(1);

  return Functions;
}

int main(int argv, char** argc) {
  LLVMContext context;
  SMDiagnostic error;
  Module *module = ParseIRFile(argc[argv-1], error, context);

  std::cout << "ll: " << argc[argv-1] << " GCNO: " << argc[argv-2] << std::endl;  
  std::string GCNO(argc[argv-2]);
  std::string GCDA(argc[argv-3]);
  GCOVFile GF;

  ErrorOr<std::unique_ptr<MemoryBuffer>> GCNO_Buff =
    MemoryBuffer::getFileOrSTDIN(GCNO);
  ErrorOr<std::unique_ptr<MemoryBuffer>> GCDA_Buff =
    MemoryBuffer::getFileOrSTDIN(GCDA);

  GCOVBuffer GCNO_GB(GCNO_Buff.get().get());
  GCOVBuffer GCDA_GB(GCDA_Buff.get().get());

  std::vector<std::unique_ptr<GCOVFunction>> Functions 
                                          = readFunctions(GF, GCNO_GB, GCDA_GB);

  if(!Functions.size()) {
    std::cout << "Invalid .gcno File!\n";
    return 0;
  }

  int i = 0;
  for(auto &func : Functions) {
    std::cout << "Função: " << func->getName().str() << " : " 
              << func->getEntryCount() << std::endl;
    for(auto I = func->block_begin(), E = func->block_end(); I != E; ++I) {
      std::cout << "bloco: "<< i << " " << (*I)->getCount() << std::endl;
      i++;
    }
  }

  return 0;
}
