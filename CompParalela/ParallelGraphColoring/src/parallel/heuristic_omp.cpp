#include "include/merge_sort_parallel.hpp"
#include "include/heuristic_omp.hpp"
#include "omp.h"

ColorGraphHeuristicParallelOpenMP::ColorGraphHeuristicParallelOpenMP(string dividerType) {
  graphDivider = getGraphDivider(dividerType);
}

// A Comparison of Parallel Graph Coloring Algorithms - J. R. Allwright, C. L. Martin
// The parallel Jones-Plassmann algorithm for coloring a graph. Page 8.
void ColorGraphHeuristicParallelOpenMP::colour(Graph* g) {
  int number_of_threads = omp_get_max_threads();
  
  vector<vector<Vertex>> l = graphDivider->divide(g, number_of_threads);

  int numberOfStalls = 0;

  #pragma omp parallel for
  for(int i = 0; i < (signed) l.size(); i++) {
    while(l[i].size() > 0) {
      vector<Vertex> I  = getMaximumInNeighbours(g, l[i]);
      cout << " " << i << " " << I.size() << endl;
      if(isAStall(I)) numberOfStalls++;

      for(auto& v : I) {
        auto v1 = g->getVertex(v.getId());
        vector<int> colors = getAllNeighboursColors(g, v1);
        v1->setColor(minimumColorNotIn(colors));
      }

      l[i] = removeFrom(l[i], I);
    }
  }

  if(PRINT_STALLS)
    cout << "stalls: " << numberOfStalls << endl; 
} 
