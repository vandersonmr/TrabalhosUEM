#include "include/heuristic.hpp"
#include <algorithm>
//#include "sequential/include/merge_sort_sequential.hpp"

vector<Vertex> ColorGraphHeuristic::getMaximumInNeighbours(Graph* g, vector<Vertex>& U) {
  vector<Vertex> I;
  for(auto v : U) {
    bool isMaximum = true;
    for(auto neighbour : v.getEdges()) {
      if(g->getVertex(neighbour)->getColor() == 0) {
        if(g->getVertex(neighbour)->getDegree() == v.getDegree()) {
          if(g->getVertex(neighbour)->getWeight() > v.getWeight()) {
            isMaximum=false;
            break;
          }
        } else if(g->getVertex(neighbour)->getDegree() > v.getDegree()) {
          isMaximum = false;
          break;
        }
      }
    }
    if(isMaximum) 
      I.push_back(v);
  }
  return I;
}


vector<int> ColorGraphHeuristic::getAllNeighboursColors(Graph* g, Vertex* v) { 
  vector<int> colors;
  for(auto neighbors : v->getEdges()) {
    auto i = g->getVertex(neighbors);
    if(i->getColor() != 0)
      colors.push_back(i->getColor());
  }
  return colors;
}

int ColorGraphHeuristic::minimumColorNotIn(vector<int>& colors) {
  sort(colors.begin(), colors.end());
  colors.erase( unique( colors.begin(), colors.end() ), colors.end() );
  int minimumColor = 1;
  for(int color : colors) {
    if(color == minimumColor)  
      minimumColor++;
    else 
      break;
  }

  if(getNumberOfColours() < minimumColor) 
    setNumberOfColours(minimumColor);

  return minimumColor;
}

vector<Vertex> ColorGraphHeuristic::getSortedListOfVertex(Graph* g) {
  //vector<Vertex> l;
  vector<Vertex> v = g->getVertexs();
  /*for(auto i : v)
    l.push_front(i);*/

  return v;
}

// Return = A - B
vector<Vertex> ColorGraphHeuristic::removeFrom(vector<Vertex>& A, vector<Vertex>& B) {
  auto pos = A.begin();
  while(pos != A.end()) {
    bool hasErase = false;
    for(auto b : B) {
      if((*pos).getId() == b.getId()) {
        pos = A.erase(pos);
        hasErase = true;;
        break;
      }
    }
    if (!hasErase)
      pos++;
  } 
  return A;
}
