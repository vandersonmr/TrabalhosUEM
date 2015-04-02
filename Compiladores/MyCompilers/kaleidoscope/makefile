all:
	clang++ -g -O0 -I/usr/include -Iincludes/ main.cpp scanner/scanner.cpp parser/parser.cpp IR/llvm.cpp `llvm-config --cppflags --ldflags --libs core` -o compiler -std=c++11 
teste:
	clang++ -g -O3 -I/usr/include teste.cpp `llvm-config --cppflags --ldflags --libs core` -o compiler 
