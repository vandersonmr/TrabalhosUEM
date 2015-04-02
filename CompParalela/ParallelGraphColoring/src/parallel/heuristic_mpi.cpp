#include "include/merge_sort_parallel.hpp"
#include "include/heuristic_mpi.hpp"
#include <algorithm>
#include <mpi.h>

ColorGraphHeuristicParallelMPI::ColorGraphHeuristicParallelMPI(string dividerType) {
  graphDivider = getGraphDivider(dividerType);
}

void syncronizeMPI(int i, int number_of_threads, vector<int>& tabu_list, vector<Vertex>& I, Graph* g) {
  for(int u=0; u < number_of_threads; u++) {
    if(u != i && (find(tabu_list.begin(), tabu_list.end(), u) == tabu_list.end())) {
      #pragma omp parallel sections 
      {
        #pragma omp section
        {
          int size = I.size(); 
          MPI_Send(&size, 1, MPI_INT, u, 20, MPI_COMM_WORLD);   
          int arr[2*I.size()];
          for(int h=0; h < I.size(); h++) {
            arr[h] = I[h].getId();
            arr[size+h] = g->getVertex(arr[h])->getColor();
          }
          MPI_Send(arr, 2*I.size(), MPI_INT, u, 21, MPI_COMM_WORLD);   
        }

        #pragma omp section 
        {
          int size;
          MPI_Status s;
          MPI_Recv(&size, 1, MPI_INT, u, 20, MPI_COMM_WORLD, &s);
          if(size == -1) {
            tabu_list.push_back(u);
          } else {
            int arr[size];
            MPI_Recv(arr, 2*size, MPI_INT, u, 21, MPI_COMM_WORLD, &s);
            for(int h=0; h < size; h++) {
              auto v1 = g->getVertex(arr[h]);
              v1->setColor(arr[size+h]);
            }
          }
        }
      } 
    }
  }

}

void finalizeMPI(int number_of_threads) {
  for(int u=0; u < number_of_threads; u++) {
    int size = -1;
    MPI_Send(&size, 1, MPI_INT, u, 20, MPI_COMM_WORLD);
  }
}
// A Comparison of Parallel Graph Coloring Algorithms - J. R. Allwright, C. L. Martin
// The parallel Jones-Plassmann algorithm for coloring a graph. Page 8.
void ColorGraphHeuristicParallelMPI::colour(Graph* g) {
  MPI_Init(NULL, NULL);

  int number_of_threads_mpi;
  MPI_Comm_size(MPI_COMM_WORLD, &number_of_threads_mpi);

  vector<vector<Vertex>> l = graphDivider->divide(g, number_of_threads_mpi);
  
  int numberOfStalls = 0;

  int i;
  MPI_Comm_rank(MPI_COMM_WORLD, &i);

  vector<int> tabu_list;
  while(l[i].size() > 0) {
    vector<Vertex> I  = getMaximumInNeighbours(g, l[i]);

    if(isAStall(I)) numberOfStalls++;
    
    for(auto& v : I) {
      auto v1 = g->getVertex(v.getId());
      vector<int> colors = getAllNeighboursColors(g, v1);
      v1->setColor(minimumColorNotIn(colors));
    }

    syncronizeMPI(i, number_of_threads_mpi, tabu_list, I, g);
    l[i] = removeFrom(l[i], I);
  }
  finalizeMPI(number_of_threads_mpi);

  if(PRINT_STALLS)
    cout << "stalls: " << numberOfStalls << endl; 

  MPI_Finalize(); 
}

