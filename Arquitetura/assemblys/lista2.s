/*
	Implemetação LISTA em GAS.
	Diogo Takayuki Murata <diogomurat@gmail.com>
	Vanderson M. do Rosario <vandersonmr2@gmail.com>
	Victor Glauber L. Silva <victor_glauber@hotmail.com>
	Under MIT License.

	struct l{
		int x;
		lista* next;
	} lista;
*/

.comm lista,4,4
.globl _start

.type alocaEstrutura,@function
.type enfilera,@function
.type buscarNaFila,@function
.type tiraDaFila,@function
.data
	quantidade: .int 0
	aux: .int 0
	size: .int 12
	namesize: .int 50
	curso: .int 40	

	clear: .string "clear"
	menuTitulo: .asciz "Escolha uma opcao"
	op1: .asciz "\n1 - Inserir FIFO"
	op11: .asciz "\n Digite um valor inteiro:\n"
	op2: .asciz "\n2 - Remover FIFO"
	op3: .asciz "\n3 - Buscar valor"
	op33: .asciz "\n Digite um valor inteiro\n"
	op4: .asciz "\n4 - Sair \n"
	res11: .asciz "\nRA %d inserido com sucesso"
	res21: .asciz "\n\nRA %d removido com sucesso\n"
	res22: .asciz "\n\n Pilha vazia\n\n"
	res31: .asciz "\nRA %d existe na fila\n"
	res32: .asciz "\nRA não existe na fila\n"
	sc1: .asciz "%d"

	pedenome: .asciz "\nDigite o nome:\n "
	pedera: .asciz "\nDigite o ra:\n "
	pedecurso: .asciz "\nDigite o nome do curso:\n "

	mostranome: .asciz "\n Nome: %s \n"
	mostrara: .asciz "\n RA: %d \n"
	mostracurso: .asciz "\n Curso %s \n"

	formastr: .asciz "%s"
	formach: .asciz "%c"
	formanum: .asciz "%d"

.text

/* test* alocaEstrutura(); */
alocaEstrutura:
	pushl %ebp
	movl %esp,%ebp
	
	subl $4,%esp
	movl size,%eax
	movl %eax,(%esp)

	call malloc
	movl $0 ,(%eax)
	movl $0 ,4(%eax)
	push %eax
	
	movl %ebp,%esp	
	pop %ebp
	ret
/*--------------------------------------- */

/* void enfilera(fila* f,int x) */
enfilera:
	pushl %ebp
	movl %esp,%ebp
	
	// EBX contem o novo registro
	call alocaEstrutura
	movl -16(%esp),%ebx

	// Pega paramentros; EAX = Fila* e ECX = x;
	movl 8(%esp),%eax
	movl 12(%esp),%ecx
	

	// Seta EBX->value = ECX; EBX->Next = 0; 
	movl %ecx,0(%ebx)
	movl 16(%esp),%ecx
	movl %ecx,8(%ebx)
	movl $0,4(%ebx)
	
	movl %eax,%edx
	cmp $0,%edx
	jne difNull
 
filaVazia:
	movl %ebx, lista
	jmp fim

/* While (q!=null) q = q->prox; */
difNull:
	cmp $0,4(%edx)
	je igualNull
	movl 4(%edx),%edx
	jmp difNull
igualNull:
	// EDX->Next = EBX;
	movl %ebx,4(%edx)
fim:
	movl %ebp,%esp
	pop %ebp
	ret
/*--------------------------------------- */

/* int tiraDaFila(fila* f,int x); */
tiraDaFila:
	push %ebp
	movl %esp,%ebp
	
	movl 8(%esp),%edx
        movl 12(%esp),%ecx
	movl $-1,%ebx
difr:
        cmp %ecx, (%edx)
        je igualr
        cmp $0,4(%edx)
        je naoEncontrour
	movl %edx,%ebx
        movl 4(%edx),%edx
        jmp difr

naoEncontrour:
	pushl $-999
        jmp return
vazior:
	movl %ecx,lista
	jmp return 
igualr:
        pushl %ecx
	movl 4(%edx),%ecx
	cmp $-1,%ebx
	je vazior	
	movl %ecx,4(%ebx)

return:
	movl %ebp,%esp
	pop %ebp
	ret
/*--------------------------------------- */

/* node* buscarNaFila(fila* f,int x); */
buscarNaFila:
	pushl %ebp
	movl %esp,%ebp
	
	movl 8(%esp),%edx
	movl 12(%esp),%ecx
	
dif:
	cmp %ecx, (%edx)
	je igual
	cmp $0,4(%edx)
	je naoEncontrou
	movl 4(%edx),%edx
	jmp dif

naoEncontrou:
	pushl $-999
	jmp sai
igual:
	pushl %edx

sai:
	movl %ebp,%esp
	pop %ebp
	ret
/*--------------------------------------- */

menu:
	pushl %ebp
	movl %esp,%ebp
loop:
	pushl $clear
	call system
	
	pushl $menuTitulo
	call printf

	pushl $op1
	call printf

	pushl $op2
	call printf

	pushl $op3
	call printf
	
	pushl $op4
	call printf
	
	addl $20,%esp

	pushl $aux
	pushl $sc1
	call scanf
	add $8,%esp

	cmp $1,aux
	je insere
	cmp $4,aux
	je sair	
	cmp $2,aux
	je remove
	cmp $3,aux
	je busca

	jmp loop

insere:
	
	pushl $pedera
	call printf
	
	pushl $aux
	pushl $sc1
	call scanf
	add $8,%esp	

	//Ronald code here.
	pushl $100
	call malloc
	pushl %eax	
	
	pushl $formach # para remover o enter
	call scanf
	addl $4, %esp

	pushl $pedenome
	call printf
	addl $4,%esp
	call gets
	
	popl %eax
	addl $50,%eax
	pushl %eax

	pushl $pedecurso
	call printf
	addl $4, %esp
	call gets

	popl %eax
	subl $50,%eax
	
	pushl %eax		
	pushl aux
	pushl lista
	call enfilera
	add $12,%esp

	addl $1,quantidade	

	jmp loop

remove:
	cmp $0,quantidade
	je empty

        pushl $aux
        pushl $sc1
        call scanf
        add $8,%esp


	pushl aux
        pushl lista
	call tiraDaFila
	movl -12(%esp),%eax
	
	subl $1,quantidade

	pushl %eax
	pushl $res21
	call printf
	add $8,%esp
	jmp termina

empty:
	pushl $res22
	call printf	
	add $4,%esp

termina:
	call getchar
	call getchar

	jmp loop
	
	
busca:
	cmp $0,quantidade
	je empty
	
	pushl $aux
        pushl $sc1
        call scanf
        add $8,%esp

        pushl aux
        pushl lista
	call buscarNaFila
	movl -12(%esp),%eax	
	addl $8,%esp

	cmp $-999,%eax
	je nig

ig:	
	pushl %eax
	pushl (%eax)
	pushl $res31
	call printf
	addl $8,%esp
	
	popl %eax
	addl $8,%eax
	pushl (%eax)

	pushl (%eax)
	pushl $mostranome
	call printf
	add $8,%esp
		
	popl %eax
	addl $50,%eax

	pushl %eax
	pushl $mostracurso
	call printf
	add $12,%esp
	
	jmp termina
	
nig:
	pushl $res32
	call printf
	addl $8,%esp
	jmp termina

sair:
	movl %ebp,%esp
	pop %ebp
	ret 
/*--------------------------------------- */
	
/* lista = alocaEstrutura(); */
_start:
	movl $0,quantidade
	call menu

exit:
	movl $1,%eax
	movl $0,%ebx
	int $0x80
/*--------------------------------------- */
