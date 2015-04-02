#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "execution.h"

FILE* file;

void openFile(char dir[]){
	file = fopen(dir,"r");
	if(file == NULL){
		printf("Erro ao abrir arquivo!\n");
		exit(1);
	}
}

void closeFile(){
	fclose(file);
}


memoryBlock* parseLine(char line[]){
	memoryBlock* block = malloc(sizeof(memoryBlock));

	char *opcode = malloc(sizeof(char)*255);
	char *operandos = malloc(sizeof(char)*255);

	int memAddr;
	sscanf(line,"%d	%[^\t\n] %s",&memAddr,opcode,
						operandos);
	
	if(*opcode=='\"'){
		opcode++;
		while(*opcode != '"'){
			memoryBlock* blockAux = malloc(sizeof(memoryBlock));
			blockAux->pos = memAddr++;
			char *c = malloc(2);
			*c = *(opcode++);
			c++;
			*c = 64; 
			blockAux->opcode = --c;
			blockAux->operando1 = NULL;
			blockAux->operando2 = NULL;
			blockAux->operando3 = NULL;
			addMemory(blockAux);
		}
		
		memAddr = -1;
	}
	block->pos = memAddr;
	block->opcode = opcode;
	
	char *operando1 = malloc(sizeof(char)*255);
	char *operando2 = malloc(sizeof(char)*255);
	char *operando3 = malloc(sizeof(char)*255);
	sscanf(operandos,"%[^','],%[^','],%[^',']",operando1,operando2,
					operando3);
	block->operando1 = operando1;
	block->operando2 = operando2;
	block->operando3 = operando3;	

	return block;
}

int main(int argc, char* argv[]){
	char line[LINE_SIZE];
	memoryBlock* blockAux;
	char *fileName = NULL;

	int isSteps = 0;
	int isToShowRegs = 0;
	int isToShowMem = 0;
	int isToVerbose = 0;

	int x;

	for(x=0; x < argc; x++){
		char *s = argv[x];
		if(strcmp(s,"-s") == 0)
			fileName = argv[x+1];
		if(strcmp(s,"-S") == 0)
			isSteps = 1;
		if(strcmp(s,"-m") == 0)
			isToShowMem = 1;
		if(strcmp(s,"-r") == 0)
			isToShowRegs = 1;	
		if(strcmp(s,"-v") == 0)
			isToVerbose = 1;
	}

	if (fileName == NULL){
		printf("Nome do arquivo não especificado.\n");
		exit(1);
	}

	memoryClean();
	openFile(fileName);

	void* r = fgets(line,LINE_SIZE,file); 
	if(r == NULL){
		printf("Arquivo vazio!\n");
		exit(1);
	}

	int PC;
	sscanf(line,"#init %d",&PC);	
	while(NULL != fgets(line,LINE_SIZE,file)){
		blockAux = parseLine(line);
		addMemory(blockAux);
	}

	closeFile();
			
	startSimulation(PC,isSteps,isToShowMem,isToShowRegs,
					isToVerbose);
	
	
	return 0;
}
