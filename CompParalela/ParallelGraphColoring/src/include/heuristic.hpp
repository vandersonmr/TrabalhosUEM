#ifndef GRAPH_H
#define GRAPH_H

#include "graph.hpp"
#include "vertex.hpp"
#include "merge_sort.hpp"
#include <list>
#include <vector>
#include <string>

using namespace std;

class ColorGraphHeuristic {
  protected:
    vector<Vertex> getMaximumInNeighbours(Graph*, vector<Vertex>&);
    vector<Vertex> removeFrom(vector<Vertex>&, vector<Vertex>&);
    vector<int>    getAllNeighboursColors(Graph*, Vertex*);
    vector<Vertex> getSortedListOfVertex(Graph*);
    int            minimumColorNotIn(vector<int>&);

    int  numberOfColours = 0;
    void setNumberOfColours(int c) { numberOfColours = c;};
  public:
    virtual void colour(Graph*) {};
    int          getNumberOfColours() { return numberOfColours;};
};
#endif
