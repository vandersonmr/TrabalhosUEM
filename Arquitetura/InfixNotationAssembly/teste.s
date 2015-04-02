.section .data
	nome:	.asciz "op.txt"
.section .bss
	.lcomm buffer 100
	.lcomm handle 4
	.lcomm pilhaAux 100
	.lcomm saidaPosfixa 100
.section .text
.globl _start
_start:
	nop
	jmp open

.type lerCaracter,@function
lerCaracter:
	pushl %ebp
        movl %esp,%ebp
        movl 8(%ebp),%edi	
	movl $0,%eax
	movb buffer(,%edi,1),%al
        movl %ebp,%esp
        pop %ebp
        ret	

trataInfixo:
	pushl %ebx
	call lerCaracter
	inc %ebx
	cmp $48,%eax
	jge enviaSaida
	cmp $10,%eax
	je trataFIM
	jmp trataOperador
	

	
trataAbrePare:
	movl $40,pilhaAux(,%ecx,4)
	inc %ecx
	jmp trataInfixo

trataFechaPare:
			
trataOperador:
	cmp $0,%ecx
	je empilhaAux
	cmp $43,%eax
	je trataOperadorSS
	cmp $45,%eax
	je trataOperadorSS
	jmp trataOperadorMD

trataOperadorSS:
	sub $1,%ecx
	cmp $43,pilhaAux(,%ecx,4)
	je trataAux
	cmp $45,pilhaAux(,%ecx,4)
	je trataAux
	jmp trataDesempilha
	
trataOperadorMD:
	jmp empilhaAux

trataAux:
	inc %ecx

empilhaAux:
	movl %eax,pilhaAux(,%ecx,4)
	inc %ecx
	jmp trataInfixo

trataDesempilha:	
	inc %ecx

desempilhaAux:
	sub $1,%ecx
	movl pilhaAux(,%ecx,4),%esi
	movl %esi,saidaPosfixa(,%edx,4)
	inc %edx
	jmp empilhaAux

enviaSaida:
	movl %eax,saidaPosfixa(,%edx,4)
	inc %edx
	jmp trataInfixo

trataFIM:
	cmp $0,%ecx
	je fim

trataFIM2:
	sub $1,%ecx
	movl pilhaAux(,%ecx,4),%esi
        movl %esi,saidaPosfixa(,%edx,4)
        inc %edx
	jmp trataFIM

open:
	movl $5,%eax
	movl $nome,%ebx
	movl $00, %ecx
	movl $0444, %edx
	int $0x80
	test %eax, %eax
	js badfile
	movl %eax, handle

read:
	movl $3, %eax
	movl handle, %ebx
	movl $buffer, %ecx
	movl $42, %edx
	int $0x80
	test %eax, %eax
	js badfile
	movl $0,%ebx
	movl $0,%ecx
	movl $0,%edx
	jmp trataInfixo

print:
	movl $4, %eax
	movl $1, %ebx
	movl $buffer, %ecx
	movl $42, %edx
	int $0x80
	test %eax, %eax
	js badfile

fecha:
	movl $6, %eax
	movl handle, %ebx
	int $0x80


badfile:
	jmp fim
fim:
	movl $1,%eax
	movl $0,%ebx
	int $0x80

