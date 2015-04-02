#include "include/divisor.hpp"

vector<vector<Vertex>> DivisorGraphDivider::divide(Graph* g, int number) {
  vector<Vertex> l = g->getVertexs();

  vector<vector<Vertex>> v(number);
  for(int i=0; i < number; i++) 
    v[i] = vector<Vertex>();
  
  int divisor = (l.size()+number) / number;
  for(auto i : l) {
    int id = i.getId();
    v[id/divisor].push_back(i);
  }
  
  return v;
}


