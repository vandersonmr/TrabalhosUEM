#include "include/greedy.hpp"
#include <queue>
#include <algorithm>

using namespace std;
// BFS
vector<vector<Vertex>> GreedyGraphDivider::divide(Graph* g, int number) {
  vector<vector<Vertex>> v;

  auto less = [g](const int& a,const int& b) -> bool { return g->getVertex(a)->getEdges().size() >
                                                              g->getVertex(b)->getEdges().size();};

  for(auto& j : g->getVertexs()) {
    g->getVertex(j.getId())->setColor(-1);
  }

  int block_size = g->getVertexs().size()/number;
  for(int i = 0; i < number; i++) {
    vector<Vertex> v1;
    queue<int> next;
 
    int pos;
    for(auto j : g->getVertexs()) {
      if(j.getColor() == -1) {
        pos = j.getId();
        break;
      }
    }

    next.push(pos);
    while(v1.size() < block_size) {
      if(next.size() == 0) {
        int pos;
        for(auto j : g->getVertexs()) {
          if(j.getColor() == -1) {
            pos = j.getId();
            break;
          }
        }
        next.push(pos);
      }

      int elem = next.front();
      next.pop();
      if (g->getVertex(elem)->getColor() == 0) continue;
      vector<int> e = g->getVertex(elem)->getEdges();
      sort(e.begin(), e.end(), less);
      for(auto n : e) {
        next.push(n);
      }

      g->getVertex(elem)->setColor(0);
      v1.push_back(*(g->getVertex(elem)));

    } 
    v.push_back(v1);
  }
  return v;
}
