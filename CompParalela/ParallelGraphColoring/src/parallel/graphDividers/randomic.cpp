#include "include/randomic.hpp"

vector<vector<Vertex>> RandomicGraphDivider::divide(Graph* g, int number) {
    vector<Vertex> l = g->getVertexs();

      vector<vector<Vertex>> v;
        int block_size = l.size()/number;
          auto it = l.begin();
            for(int i = 0; i < number; i++) {
                  auto lastIt = it;
                      advance(it, block_size);

                          if(i == 0) {
                                  advance(it, l.size()%number);
                                      }
                            
                              vector<Vertex> v1(lastIt, it);
                                  v.push_back(v1);
                                    }
              
              return v;
}


