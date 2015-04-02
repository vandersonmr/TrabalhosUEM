#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

memoryBlock * memory[MEMORY_SIZE];

void addMemory(memoryBlock * memBk){
	int pos = memBk->pos;
	if(pos >= 0 && pos <= MEMORY_SIZE){
		memory[memBk->pos] = memBk;
	}
}

memoryBlock* getMemoryAt(int pos){
	if(pos <= MEMORY_SIZE){
		return memory[pos];
	}else{
		printf("Tentativa de acesso a região não existente da memória!");
		exit(0);
	}	
}

void memoryClean(){
        int i;
        for(i=0;i < MEMORY_SIZE;i++){
		memoryBlock *nop = malloc(sizeof(memoryBlock));                
		nop->opcode = NULL;
		nop->operando1 = NULL;
		nop->operando2 = NULL;
		nop->operando3 = NULL;
		nop->pos = i;
                addMemory(nop);
        }
}

