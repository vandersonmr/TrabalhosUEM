#include "include/heuristic.hpp"
#include "sequential/include/heuristic.hpp"
#include "parallel/include/heuristic_omp.hpp"
#include "parallel/include/heuristic_mpi.hpp"
#include "omp.h"
#include <cstring>

void failure() {
    cout << "Need more information: ./program -p/-s filePath" << endl;
    exit(1);
}

int main(int argc, char* argv[]) {
  if(argc <= 2) failure(); 
  else {
    ColorGraphHeuristic* heuristic;
    bool printNumberOfColours = false;
    char *filePath = NULL;
    for(int i=1; i < argc; i++) {
      string argument(argv[i]);
      if (argument == "-s") {
        filePath = argv[i+1];
        heuristic = new ColorGraphHeuristicSequential;
      } else if (argument == "--omp" || argument == "--mpi") {
        int p;
        filePath = argv[i+3];
        sscanf(argv[i+1],"%d",&p);
        omp_set_num_threads(p);
        if(argument == "--omp") {
          heuristic = new ColorGraphHeuristicParallelOpenMP(string(argv[i+2]));
        } else {
          heuristic = new ColorGraphHeuristicParallelMPI(string(argv[i+2]));
        }
      } else if (argument == "-ps") {
        ((ColorGraphHeuristicParallel*) heuristic)->printStalls(true);
      } else if (argument == "-pc") {
        printNumberOfColours = true;
      }
    }
    
    if(filePath == NULL) failure();

    Graph g(filePath);
    heuristic->colour(&g);

    if(printNumberOfColours) 
      cout << "Colours: "<< heuristic->getNumberOfColours() << endl;

    return 0;
  }
}
