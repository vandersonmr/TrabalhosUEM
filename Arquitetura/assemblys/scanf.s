/*
	Implementação SCANF em GAS.
	Vanderson M. do Rosario <vandersonmr2@gmail.com>
	Diogo Takayuki Murata <diogomurat@gmail.com>
	Victor Glauber L. Silva <victor_glauber@hotmail.com>
	Under MIT License.
*/

.globl myScanf
.globl read
.type read,@function
.type myScanf,@function
.comm aux,1
.comm aux2,100
.comm aux3,4
.data
	
	base: .int 1, 10, 100, 1000, 10000, 100000
	enter: .ascii "\n"
.text

//------------------------------------//

read: // void read(char* s)
	pushl %ebp
	pushl %esi
	movl %esp,%ebp

	movl 12(%esp),%esi
_until:	
	movl $3,%eax
	movl $0,%ebx
	movl $1,%edx
	movl $aux,%ecx	
	int $0x80
	nop
	movl aux,%ecx

	cmp enter,%ecx
	je _sair
	movb %cl, (%esi)
	inc %esi
	jmp _until

_sair:
	movl %ebp,%esp
	pop %esi
	pop %ebp
	ret

//------------------------------------//

myScanf: // void scanf(char* s, ...)
	pushl %ebp
	movl %esp,%ebp
	
	movl 8(%esp),%esi
	movl $0,%edi

	movl (%esi),%eax
	cmp $37,%al
	je _trataSimbol
	jmp _exit

_trataSimbol:
       movl  12(%esp,%edi,4),%eax
        movl %eax,aux3

	movb 1(%esi),%al
	cmp $100,%al
	je d
	
	pushl 12(%esp,%edi,4)
	call read	

	movl 1(%esi),%eax
	jmp _exit

d:
	pushl $aux2
	call read
	movl $aux2,%esi
	movl $0,%ecx
_each:	
	movl $0,%eax
	movb (%esi),%al
	cmp $0,%eax
	je proc 
	inc %esi
	pushl %eax
	jmp _each

proc:
	movl $0,%ecx
	movl $base,%edi	
proc1:
	movl $aux2,%eax
	cmp %esi,%eax
	je save
	pop %eax
	subl $48,%eax
	movl (%edi),%ebx
	mul %ebx
	movl %eax,%ebx
	addl $4,%edi
	addl %ebx,%ecx
	subl $1,%esi
	jmp proc1
	
save:
	movl aux3,%eax
	movl %ecx,(%eax)

_exit:
	movl %ebp,%esp
	pop %ebp
	ret


