#ifndef LOGICUNIT_H
#define LOGICUNIT_H

void mov(memoryBlock*);
void add(memoryBlock*);
void sys(memoryBlock*);
void sub(memoryBlock*);
void pdiv(memoryBlock*);
void mul(memoryBlock*);
void rest(memoryBlock*);
void jump(memoryBlock*);
void jumpn(memoryBlock*);
void jumpp(memoryBlock*);
void jumpz(memoryBlock*);
void ld(memoryBlock*);
void st(memoryBlock*);
void push(memoryBlock*);
void pop(memoryBlock*);
void call(memoryBlock*);
void ret();

#endif
