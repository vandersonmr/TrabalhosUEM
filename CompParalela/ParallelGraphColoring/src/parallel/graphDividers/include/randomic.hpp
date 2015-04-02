#include <vector>
#include "divider.hpp"

using namespace std;

class RandomicGraphDivider : public GraphDivider {
    public:
          vector<vector<Vertex>> divide(Graph*, int number);
};
