#include "include/merge_sort_sequential.hpp"
#include "include/heuristic.hpp"

// A Comparison of Parallel Graph Coloring Algorithms - J. R. Allwright, C. L. Martin
// The parallel Jones-Plassmann algorithm for coloring a graph. Page 8.
void ColorGraphHeuristicSequential::colour(Graph* g) {
  vector<Vertex> U = getSortedListOfVertex(g);

  while(U.size() > 0) {
    vector<Vertex> I  = getMaximumInNeighbours(g, U);
    for(auto& v : I) {
      auto v1 = g->getVertex(v.getId());
      vector<int> colors = getAllNeighboursColors(g, v1);
      v1->setColor(minimumColorNotIn(colors));
    }
    U = removeFrom(U, I);
  }
} 
