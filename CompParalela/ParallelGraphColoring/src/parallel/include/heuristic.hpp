#ifndef PARALLEL
#define PARALLEL
#include "../../include/heuristic.hpp"
#include "../graphDividers/include/randomic.hpp"
#include "../graphDividers/include/bfs.hpp"
#include "../graphDividers/include/divisor.hpp"
#include "../graphDividers/include/dfs.hpp"
#include "../graphDividers/include/greedy.hpp"
#include <string>

class ColorGraphHeuristicParallel : public ColorGraphHeuristic {
  protected:
    bool isAStall(vector<Vertex>&);
    bool PRINT_STALLS = false;
    GraphDivider* getGraphDivider(string);

    GraphDivider* graphDivider;
  public:
    void colour(Graph*) {};
    void printStalls(bool);

};
#endif
