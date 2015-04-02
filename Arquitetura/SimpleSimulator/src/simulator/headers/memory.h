#ifndef MEMORY_H
#define MEMORY_H

#define MEMORY_SIZE 1024
#define LINE_SIZE 30
#define MEMORY_DIGITS_SIZE 4
#define OPCODE_SIZE 10

typedef struct memoryBlock{
	char *opcode;
	int pos;
	char *operando1;
	char *operando2;
	char *operando3;
}memoryBlock;


void memoryClean();

void addMemory(memoryBlock*);

memoryBlock* getMemoryAt(int);

memoryBlock* nop;
#endif
