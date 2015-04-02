#include "include/merge_sort_parallel.hpp"
#include "include/heuristic.hpp"
#include "omp.h"

GraphDivider* ColorGraphHeuristicParallel::getGraphDivider(string dividerType) {
  GraphDivider* graphDivider;

  if      (dividerType == "randomic") 
    graphDivider = new RandomicGraphDivider();
  else if (dividerType == "bfs")
    graphDivider = new BfsGraphDivider();
  else if (dividerType == "dfs")
    graphDivider = new DfsGraphDivider();
  else if (dividerType == "greedy")
    graphDivider = new GreedyGraphDivider();
  else if (dividerType == "divisor")
    graphDivider = new DivisorGraphDivider();
  else
    graphDivider = new RandomicGraphDivider();

  return graphDivider;
}

void ColorGraphHeuristicParallel::printStalls(bool pStalls) {
  PRINT_STALLS = pStalls;
}

bool ColorGraphHeuristicParallel::isAStall(vector<Vertex>& I) {
  return I.size() <= 0;
}

