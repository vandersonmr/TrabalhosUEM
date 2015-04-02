flags=-std=c++11 -Wall -Wextra -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -pedantic -pedantic-errors -Werror -O3
boost=-lboost_unit_test_framework
OBJ=graph.o heuristic.o merge_sort.o

all: $(OBJ)

%.o: %.cpp
	    g++ $(flags) -c -o $@ $<

clear:
	rm *.o -f

