#include <vector>
#include "divider.hpp"

using namespace std;

class DfsGraphDivider : public GraphDivider {
  public:
    vector<vector<Vertex>> divide(Graph*, int number);
};
