#include <vector>
#include "divider.hpp"

using namespace std;

class GreedyGraphDivider : public GraphDivider {
  public:
    vector<vector<Vertex>> divide(Graph*, int number);
};
