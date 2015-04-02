#include "memory.h"
#include "registerBank.h"
#include <stdio.h>

void printMem(){
	printf("\n\n### MEMORY ###\n\n");
	int pos = 0;
	memoryBlock* memBlock;
	while(pos < MEMORY_SIZE){
		memBlock = getMemoryAt(pos);
		if(memBlock->opcode != NULL){
			printf("Pos mem: %d \nvalor: %s\n",pos,memBlock->opcode);
		}
		pos++;
	}
	printf("\n######\n");
}

void printRegs(){
	printf("\n\n### REGISTRADORES ###\n\n");
	int regAddr;
	memoryBlock* memBlock;
	for(regAddr=0;regAddr<REGISTERBANK_SIZE;regAddr++){
		memBlock = getRegister(regAddr);
		if(memBlock->opcode != NULL){
			printf("Reg: %c\nValor: %s\n",(char)regAddr+97,memBlock->opcode);
		}
	}
	printf("\n######\n");
}

