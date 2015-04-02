#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "vertex.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

class Graph {
  private:
    int size = 0;
    unique_ptr<unordered_map<int,Vertex*>> vertexs;
    Vertex* vertexs_;
    int loadGraph(string);
    int alocGraphStruct();
    void addVertex(int);
    void addEdge(int, int);
  public:
    Graph(string);
    int getSize();
    Vertex* getVertex(int i);
    vector<Vertex> getVertexs();
};
#endif
