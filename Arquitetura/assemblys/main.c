#include <stdlib.h>

int main(void){
	
	char *nome = malloc(100);	
	char s;
	int i =67 ;
	
	myPrintf("Digite sua idade:\n");
	myScanf("%d",&i);
	myPrintf("Digite seu nome:\n");
	myScanf("%s",nome);
	myPrintf("Digite seu sexo (m/f):\n");
	myScanf("%c",&s);
	if(i > 18){
		myPrintf("Ola %s. Você é maior de idade. Você tem %d anos. E é do sexo: %c \n",nome,i,s);
	}else{	
		myPrintf("Ola %s. Você é menor de idade. Você tem %d anos. E é do sexo: %c \n",nome,i,s);	
	}
	return 0;
}
