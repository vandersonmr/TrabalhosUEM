#ifndef VERTEX_H
#define VERTEX_H
#include "uniq_random_generator.hpp"
#include <vector>

using namespace std;

class Vertex {
  private:
    long weight = uniqRandomGenerator::rand();
    int color = 0;
    vector<int> edges;
    long id;
  public:
    long getId    () const { return id;           };
    long getDegree() const { return edges.size(); };
    long getWeight() const { return weight;       };
    int  getColor () const { return color;        };

    vector<int> getEdges () { return edges; };

    void setWeight(long weight) { this->weight = weight; };
    void setColor (int color)   { this->color  = color;  };
    void setId    (long id)     { this->id     = id;     };

    void addEdge  (int new_edge){ edges.push_back(new_edge);}; 
};
#endif
