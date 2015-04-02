#include "memory.h"
#include "registerBank.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int PC = 0;
memoryBlock* registerBank[REGISTERBANK_SIZE];

void initReg(){
	int i=0;
	for(i=0;i<REGISTERBANK_SIZE;i++){
		registerBank[i] = malloc(sizeof(memoryBlock));
		registerBank[i]->opcode = NULL;
	}
}

void setRegister(int addr,memoryBlock *data){
	if(addr <= REGISTERBANK_SIZE)
		registerBank[addr] = data;		
		
	
}

memoryBlock* getRegister(int addr){
	if(addr <= REGISTERBANK_SIZE)
		return registerBank[addr];
	else 
		return NULL;
}

int getPC(){
	return PC;
}

void setPC(int x){
	if(x > MEMORY_SIZE || x < 0){
		printf("Jump para região não existente da memória!");
		exit(1);	
	}

	PC = x;
}


