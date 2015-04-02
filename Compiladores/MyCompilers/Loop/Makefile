all:
	cd parser; make; cd ..;
	clang++ -O0 -I./ IR.cpp parser/*.o -std=c++11 `llvm-config --cppflags --ldflags --libs core` -lpthread -lcurses -ldl -lfl -g
clean:
	cd parser; make clean; cd ..;
