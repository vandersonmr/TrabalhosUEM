flags=-std=c++11 -Wall -Werror -O3
boost=-lboost_unit_test_framework
OBJ=heuristic.o merge_sort.o

all: $(OBJ)

%.o: %.cpp
	    g++ $(flags) -c -o $@ $<

clear:
	rm *.o -f

