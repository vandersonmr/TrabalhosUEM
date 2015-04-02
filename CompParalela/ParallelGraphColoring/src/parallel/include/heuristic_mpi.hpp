#include "heuristic.hpp"
#include <string>

 class ColorGraphHeuristicParallelMPI : public ColorGraphHeuristicParallel {
  public:
    void colour(Graph*);
    ColorGraphHeuristicParallelMPI(string);
};
