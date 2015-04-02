/*
	Implementação PRINTF em GAS.
	Vanderson M. do Rosario <vandersonmr2@gmail.com>
	Diogo Takayuki Murata <diogomurat@gmail.com>
	Victor Glauber L. Silva <victor_glauber@hotmail.com>
	Under MIT License.
*/

.globl myPrintf
.globl sizeOf
.globl print

.type print,@function
.type myPrintf,@function
.type sizeOf,@function

.comm aux,4
.text

//------------------------------------//
sizeOf: // int sizeOf(char *a)
	pushl %ebp
        movl %esp,%ebp
	
	movl 8(%esp),%ecx
	movl $0, %eax

_paraCadaCaracter1:
        movb 0(%ecx,%eax,1),%bl
	inc %eax
	cmp $0,%bl
	jne _paraCadaCaracter1
	
	pushl %eax
	movl %ebp,%esp
        pop %ebp
        ret

//------------------------------------//
print: // void print(char* a,int size);
	pushl %ebp
	movl %esp,%ebp
	
	movl $4, %eax
	movl $1, %ebx
	movl 8(%esp), %edx
	movl 12(%esp), %ecx
	int $0x80

	movl %ebp,%esp
	pop %ebp
	ret

// ----------------------------------//

myPrintf: // void myPrintf(char* a,...)
	pushl %ebp
	movl %esp,%ebp
	
	movl 8(%esp),%esi	
	movl $0,%edi
	movl $0,%eax
	movl $0,%ecx
	movl $0,%ebx

_paraCadaCaracter:
	movb 0(%esi,%eax,1),%bl
	movl %esi,%ecx
	addl %eax,%ecx
	inc %eax

	cmp $37,%bl
	je _trataSimbol

	cmp $0,%bl
	je _caracterFinal

	jmp _paraCadaCaracter

_trataSimbol:
	subl %esi,%ecx
	pushl %eax
	pushl %esi
	pushl %ecx

	addl $1, %eax
	addl %eax,%esi	

	call print
	addl $4,%esp
	pop %ecx
	pop %eax
	addl %eax,%ecx
	
	movb (%ecx),%cl	
	cmp $115,%cl
	je s
	cmp $99,%cl
	je c
	cmp $100,%cl
	je d
	jmp _finaliza
	
s:
	inc %edi
	movl 8(%esp,%edi,4), %ecx
	pushl %ecx
	call sizeOf
	movl -12(%esp),%eax
	pushl %eax
	call print
	addl $8,%esp
	jmp _finaliza	

c:
        inc %edi
	movl $8,%ecx
	addl %esp,%ecx
	movl $4,%eax
	mul %edi
	addl %ecx,%eax
	pushl %eax
        pushl $1
        call print
        addl $8,%esp
	jmp _finaliza

d:	
	inc %edi
        movl 8(%esp,%edi,4), %eax
	movl $0, %edx	
	movl $0,%ebx
_loop:
	movl $10,%ecx
	divl %ecx	
	addl $48,%edx
	pushl %edx
	inc %ebx
	
	movl $0,%edx

	cmp $0,%eax
	jnz _loop
	
	_loop2:
		cmp $0,%ebx
		je _finaliza
		subl $1,%ebx
		pop %edx
		pushl %ebx	
		movl %edx,aux
		movl $aux,%edx
		pushl %edx
		pushl $1
		call print
		addl $8,%esp
		pop %ebx
		jmp _loop2

_finaliza:
	movl $0,%eax	
	jmp _paraCadaCaracter

_caracterFinal:	
	subl %esi,%ecx
	pushl %esi
        pushl %ecx
        call print

_exit:
	movl %ebp,%esp
	pop %ebp
	ret
