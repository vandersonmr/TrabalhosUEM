#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#define REGISTERBANK_SIZE 26 

void initReg();
void setRegister(int,memoryBlock*);
void setPC(int);
int getPC();

memoryBlock* getRegister(int);


int isRegisterLetter(char*);

#endif
