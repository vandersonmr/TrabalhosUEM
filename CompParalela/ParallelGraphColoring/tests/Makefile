flags=-std=c++11 -Wall -Wextra -Werror -O3
boost=-lboost_unit_test_framework

all: objs
	g++ graph_test.cpp ../src/graph.o -o graph_test.o $(flags) $(boost)
	g++ merge_sort_test.cpp ../src/graph.o ../src/merge_sort.o ../src/parallel/merge_sort.o ../src/sequential/merge_sort.o -o merge_sort_test.o $(flags) $(boost) -fopenmp
	g++ heuristic_test.cpp ../src/*.o ../src/sequential/*.o ../src/parallel/*.o $(flags) $(boost) -o heuristic_test.o -fopenmp

objs:
	    cd ../src/; \
		  make; \
			cd sequential; \
			make; \
			cd ..; \
			cd parallel; \
			make; 


clear:
	rm *.o -f

