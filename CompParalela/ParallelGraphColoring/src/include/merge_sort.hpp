#ifndef MERGESORT_H
#define MERGESORT_H
#include "uniq_random_generator.hpp"
#include "vertex.hpp"
#include <vector>

using namespace std;

class MergeSort {
  protected:
    vector<Vertex> merge(const vector<Vertex>&, const vector<Vertex>&);
    virtual vector<Vertex> mergeSort(vector<Vertex>&) = 0;
  public:
    vector<Vertex> sort(vector<Vertex>&);
};
#endif
