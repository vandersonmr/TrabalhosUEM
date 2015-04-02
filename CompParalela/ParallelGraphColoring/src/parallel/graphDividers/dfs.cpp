#include "include/dfs.hpp"
#include <stack>

// DFS
vector<vector<Vertex>> DfsGraphDivider::divide(Graph* g, int number) {
  vector<vector<Vertex>> v;

  for(auto& j : g->getVertexs()) {
    g->getVertex(j.getId())->setColor(-1);
  }

  int block_size = g->getVertexs().size()/number;
  for(int i = 0; i < number; i++) {
    vector<Vertex> v1;
    stack<int> next;
 
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

      int elem = next.top();
      next.pop();
      if (g->getVertex(elem)->getColor() == 0) continue;
      for(auto n : g->getVertex(elem)->getEdges()) {
        next.push(n);
      }

      g->getVertex(elem)->setColor(0);
      v1.push_back(*(g->getVertex(elem)));

    } 
    v.push_back(v1);
  }
  return v;
}
