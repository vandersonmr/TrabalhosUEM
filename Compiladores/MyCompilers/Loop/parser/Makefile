all:
	flex++ loop.l
	bison++ -d loop.y -o y.tab.cpp
	clang++ -I../ y.tab.cpp lex.yy.cc `llvm-config --cppflags --ldflags --libs core` -std=c++11 -w -lfl -c -fPIC -g

clean:
	rm *.o
	rm y.*
	rm lex.*
