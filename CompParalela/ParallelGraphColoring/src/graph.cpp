#include "include/graph.hpp"
#include "include/bin2asc.h"
#include <functional>

Vertex* Graph::getVertex(int i) {
  if ( i < 1 || i > size) throw("Try to acess an inexistent vertex");
  return (*vertexs)[i];
}

void Graph::addVertex(int vertex) {
  if ( vertex < 1 || vertex > size) throw("Try to add an inexistent vertex");
  if ((*vertexs)[vertex] == NULL) {
    (*vertexs)[vertex] = &(vertexs_[vertex]);//make_shared<Vertex>();
    (*vertexs)[vertex]->setId(vertex);
  }
}

void Graph::addEdge(int vertex, int edge) {
  auto v = getVertex(vertex);
  addVertex(edge); //Garante que o edge existe
  v->addEdge(edge);
  auto v1 = getVertex(edge);
  v1->addEdge(vertex);
}

int Graph::alocGraphStruct() {
  if (size > 0) { 
    vertexs_ = new Vertex[size+1]();
    vertexs = unique_ptr<unordered_map<int,Vertex*>>(new unordered_map<int,Vertex*>(size));
    return true;
  } else throw ("Size is invalid");
}

int Graph::loadGraph(string file_path) {
  string line;
  ifstream file (file_path.c_str());

  if (file.is_open()) {

    string first_line;
    getline(file,first_line);
    while(first_line.at(0) != 'p')
      getline(file, first_line);

    sscanf(first_line.c_str(), "p edge %d ", &size);

    alocGraphStruct(); 
  }

  auto populate_graph = [this] (int a, int b) {addVertex(a); addEdge(a,b);};
  write_graph_DIMACS_ascii(const_cast<char*>(file_path.c_str()), populate_graph);

  return true;
}

int Graph::getSize() {
  return size;
}

vector<Vertex> Graph::getVertexs() {
  vector<Vertex> result;
  for(auto i : *vertexs) { 
    result.push_back(*i.second);
  }
  return result;
}

Graph::Graph(string file_path) {
  bool has_read = loadGraph(file_path);
  if (!has_read) throw("Can't loadGraph"); 
}
