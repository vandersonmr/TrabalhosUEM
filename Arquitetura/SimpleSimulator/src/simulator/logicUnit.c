#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "registerBank.h"
#include "auxFunctions.h"

void _logicOP(memoryBlock *mbr,char op){

	float result = 0;
	if(isRegisterLetter(mbr->operando1)){
        	char addrRegTarget = *(mbr->operando1);
                memoryBlock* targetReg = getRegister(addrRegTarget-0x61);
                float a = strtof(mbr->operando3,NULL);
                float b = strtof(mbr->operando2,NULL);
		
		if(op=='+'){
                	result = b + a;
		}else if(op == '-'){
			result = b - a;		
		}else if(op == '*'){
			result = b * a;
		}else if(op == '/'){
			result = b / a;
		}else if(op == '%'){
			result = (int)b % (int)a;
		}
		
		char *r = itoa(result,10);
                
		targetReg->opcode = copiar(r);

                setRegister(addrRegTarget-0x61,targetReg);
        }else{
                printf("Erro: Primeiro operando da operação deve ser um registrador!\n");
                exit(1);
        }

}


void add(memoryBlock *mbr){
	_logicOP(mbr,'+');
}

void sub(memoryBlock *mbr){
	_logicOP(mbr,'-');
}

void mul(memoryBlock *mbr){
	_logicOP(mbr,'*');	
}

void pdiv(memoryBlock *mbr){
	_logicOP(mbr,'/');
}

void rest(memoryBlock *mbr){
	_logicOP(mbr,'%');
}


void _movToRegister(char* src,char target){

	memoryBlock* targetReg = getRegister(target-0x61);
       	targetReg->opcode = copiar(src);
        setRegister(target-0x61,targetReg);

}

void _movToMemory(char* src,int target){

	memoryBlock* targetMemPos = getMemoryAt(target);
       	targetMemPos->opcode = copiar(src);
        addMemory(targetMemPos);

}

void mov(memoryBlock *mbr){

	if(isRegisterLetter(mbr->operando1)){
		char c = *(mbr->operando1);
		_movToRegister(mbr->operando2,c);
	}

}

void sys(memoryBlock *mbr){
	char* src = mbr->operando1;

	if(*(mbr->operando2) == '1'){

		char *data = malloc(30);
		if (scanf("%30s",data)) {
			if(isRegisterLetter(src)){
				_movToRegister(data,*src);
			}else if(*src == '%'){
				_movToMemory(data,atoi(++src));
			}	
		}

	}else if(*(mbr->operando2) == '3'){

		if(*src == '%'){
			char* c = getMemoryAt(atoi(++src))->opcode;
			int ctrl = 0;
			while(*c != '\0' && ctrl<100){	
				c = getMemoryAt(atoi(src)+ctrl)->opcode;
				if(*c == 92)
					break;
				if(*(++c) != 64){
					printf("%s",--c);
					break; 
				}else{
					printf("%c",*(--c));
				}
				ctrl++;
			}
		}

	}else if(*(mbr->operando2) == '2'){

		char *c = NULL;
		if(*src == '%' ){
			c = getMemoryAt(atoi(++src))->opcode;
		}else if(isRegisterLetter(src)){
			c = getRegister(*src-0x61)->opcode;
		}
		if(isRegisterLetter(c)){
                       	printf("%c",*c);
               	}else{
                        printf("%.2f",atof(c));
                }

	}
}

void jump(memoryBlock *mbr){

	if(*(mbr->operando1) == '%'){	
		setPC(atoi(++mbr->operando1));
	}

}

void jumpn(memoryBlock *mbr){

	if(atoi(mbr->operando2)<0){
		jump(mbr);	
	}

}

void jumpp(memoryBlock *mbr){

	if(atoi(mbr->operando2)>=0){
		jump(mbr);	
	}

}

void jumpz(memoryBlock *mbr){

	if(atoi(mbr->operando2)==0){
		jump(mbr);	
	}

}

void ld(memoryBlock *mbr){ 

	if(isRegisterLetter(mbr->operando1)){
		char c = *(mbr->operando1);
		_movToRegister(mbr->operando2,c-0x61);
	}	

}

void st(memoryBlock *mbr){

	if(*(mbr->operando1) == '%'){
		memoryBlock *bl = getMemoryAt(atoi((++mbr->operando1)));
		bl->opcode = copiar(mbr->operando2);
	}

}

void push(memoryBlock *mbr){

	if(isRegisterLetter(mbr->operando1)){
		mbr->operando1 = 
                      copiar(getRegister((*mbr->operando1)-97)->opcode);
	}

	memoryBlock *bl = getRegister(25);
	int addr = atoi(bl->opcode);

	_movToMemory(mbr->operando1,addr);

	addr++;
	
	bl->opcode = copiar(itoa(addr,10));
	setRegister(25,bl);

}

void pop(memoryBlock *mbr){

	if(isRegisterLetter(mbr->operando1)){
		memoryBlock *bl = getRegister(25);
		int addr = atoi(bl->opcode); 
		addr--;
		bl->opcode = copiar(itoa(addr,10)); 		
		setRegister(25,bl);

		bl = getRegister(*mbr->operando1
				-0x61);
		bl->opcode = copiar(
			getMemoryAt(addr)
				->opcode);
		setRegister(*mbr->operando1
			-0x61,bl);
			
       	}	

}

void call(memoryBlock *mbr){

	memoryBlock *z = getRegister(25);
	int addr = atoi(z->opcode);
	memoryBlock *m = getMemoryAt(addr);
	m->opcode = copiar(itoa((mbr->pos+1),10));
	addMemory(m);
	addr++;
	z->opcode = copiar(itoa(addr,10));
	setRegister(25,z);

	jump(mbr);
}

void ret(){

	memoryBlock *bl = getRegister(25);
	int addr = atoi(bl->opcode); 
	addr--;
	bl->opcode = copiar(itoa(addr,10)); 		
	setRegister(25,bl);
	memoryBlock *m = getMemoryAt(addr);
	setPC(atoi(m->opcode));

}



