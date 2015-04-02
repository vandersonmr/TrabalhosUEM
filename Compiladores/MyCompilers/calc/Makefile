all:
	flex calc.l
	bison -d calc.y
	clang -o pythonzinho calc.tab.c lex.yy.c list.c -lfl -w -g	
