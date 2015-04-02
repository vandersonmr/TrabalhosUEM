flags=-std=c++11 -Wall -Werror -O3 -fopenmp
boost=-lboost_unit_test_framework
OBJ=merge_sort.o heuristic.o

all: $(OBJ)

%.o: %.cpp
	    g++ $(flags) -c -o $@ $<

clear:
	rm *.o -f

