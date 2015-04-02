all:
	clang++ -o main -O0 main.cpp -std=c++11 `llvm-config --cppflags --ldflags --libs` -lpthread -lcurses -ldl -lfl -g
clean:
	cd parser; make clean; cd ..;
