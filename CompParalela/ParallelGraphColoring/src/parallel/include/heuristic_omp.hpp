#include "heuristic.hpp"
#include <string>

 class ColorGraphHeuristicParallelOpenMP : public ColorGraphHeuristicParallel {
  public:
    void colour(Graph*);
    ColorGraphHeuristicParallelOpenMP(string);
};
