#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "registerBank.h"
#include "interface.h"
#include "logicUnit.h"
#include "auxFunctions.h"

memoryBlock *nop;
memoryBlock *mbr;

int showMemory = 0;
int showRegisters = 0;


void fetch(){
	memoryBlock *aux = getMemoryAt(getPC());
	mbr->opcode = copiar(aux->opcode);
	mbr->operando1 = copiar(aux->operando1);
	mbr->operando2 = copiar(aux->operando2);
	mbr->operando3 = copiar(aux->operando3);
	mbr->pos = aux->pos;
	setPC(getPC()+1);
}


void decode(){

	if(mbr->opcode == NULL){
                printf("ERRO: Execução de opcode nulo\n");
                exit(1);
        }
	if(mbr == nop){
		//DO NOTHING	
	}else if(mbr != NULL && mbr->operando1 != NULL){
		char *operando2 = mbr->operando2;
		char *operando3 = mbr->operando3;
		if(isRegisterLetter(operando2)){
                	mbr->operando2 =
				copiar(getRegister((*operando2)-97)->opcode);
		} 
		if(isRegisterLetter(operando3)){
			mbr->operando3 = 
				copiar(getRegister((*operando3)-97)->opcode);
                } 
		
                if(*operando2 == '%'){    
                        mbr->operando2 =
                                copiar(getMemoryAt(atoi(++operando2))->opcode);
                }
                if(*operando3 == '%'){    
                        mbr->operando3 =
                                copiar(getMemoryAt(atoi(++operando3))->opcode);
                }

	}

}

void closeSimulation(){
	if(showMemory)
		printMem();
	if(showRegisters)
		printRegs();
	exit(0);
}

void execute(){	
	if(strcmp(mbr->opcode,"exit") == 0){
		printf("\nEmulação terminada\n");
		closeSimulation();
	}
	if(strcmp(mbr->opcode,"mov") == 0){
        	mov(mbr);
	}
	if(strcmp(mbr->opcode,"add") == 0){
		add(mbr);
	}
	if(strcmp(mbr->opcode,"sys") == 0){
		sys(mbr);
	}
	if(strcmp(mbr->opcode,"sub") == 0){
		sub(mbr);
	}
	if(strcmp(mbr->opcode,"mul") == 0){
		mul(mbr);
	}
	if(strcmp(mbr->opcode,"div") == 0){
		pdiv(mbr);
	}
	if(strcmp(mbr->opcode,"rest") == 0){
		rest(mbr);
	}

	if(strcmp(mbr->opcode,"jump") == 0){
		jump(mbr);
	}
	
	if(strcmp(mbr->opcode,"jumpn") == 0){
		jumpn(mbr);
	}
	
	if(strcmp(mbr->opcode,"jumpp") == 0){
		jumpp(mbr);
	}
	
	if(strcmp(mbr->opcode,"jumpz") == 0){
		jumpz(mbr);
	}
	
	if(strcmp(mbr->opcode,"ld") == 0){
		ld(mbr);
	}
	if(strcmp(mbr->opcode,"st") == 0){
		st(mbr);
	}
	if(strcmp(mbr->opcode,"push") == 0){
		push(mbr);
	}
	if(strcmp(mbr->opcode,"pop") == 0){
		pop(mbr);
	}
	if(strcmp(mbr->opcode,"call") == 0){
		call(mbr);
	}
	if(strcmp(mbr->opcode,"ret") == 0){
		ret();
	}
	
}

int verbose = 0;
void startSimulation(int pc,int isSteps,int isToShowMem,
			int isToShowRegs,int isToVerbose){
	setPC(pc);

	verbose = 0;
	showMemory = isToShowMem;
	showRegisters = isToShowRegs;

	initReg();
	mbr = malloc(sizeof(memoryBlock));	
	while(getPC() < MEMORY_SIZE){
		if(isToVerbose){
			printf("Iniciando execução PC=%d ...",getPC());
		}
		fetch();
		if(isToVerbose){
			printf("\n opcode: %s \n \
				operando1: %s \n \
				operando2: %s \n \
				operando3: %s \n",
				mbr->opcode,mbr->operando1,
				mbr->operando2,mbr->operando3);
		}
		decode();
		execute();
		if(isToVerbose){
			printf("\ndone\n");
		}
		if(isSteps){ 
			  if(isToShowMem)
				printMem();
			  if(isToShowRegs)
				printRegs();
			  getchar();
		}
	}
	
}




