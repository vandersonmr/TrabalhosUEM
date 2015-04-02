#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Coverte inteiro para string seguindo a base. O contrario do atoi.*/
char* itoa(float val,int base){ 
	static char buf[32]={0};
	sprintf(buf,"%.2f",val);
	return &buf[0];
}

char * copiar(char *fonte){
	char *dest = malloc(strlen(fonte));
	strcpy(dest,fonte);
	return dest;
}

int isRegisterLetter(char *operando){
	if(*operando <= 0x7A 
			&& *operando >= 0x61){
		return 1;
        }
	return 0;
}


