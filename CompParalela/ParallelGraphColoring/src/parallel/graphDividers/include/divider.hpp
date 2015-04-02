#ifndef GRAPHDIVIDER_HPP
#define GRAPHDIVIDER_HPP
#include <vector>
#include "../../../include/graph.hpp"

using namespace std;

class GraphDivider {
  public:
    virtual vector<vector<Vertex>> divide(Graph*, int number) = 0;
};
#endif
