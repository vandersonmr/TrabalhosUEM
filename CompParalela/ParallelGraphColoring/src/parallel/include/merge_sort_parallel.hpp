#include "../../include/merge_sort.hpp"
#include <omp.h>

class MergeSortParallel : public MergeSort {
  private:
    vector<Vertex> mergeSort(vector<Vertex>&);
    vector<Vertex> mergeSortParallel(vector<Vertex>&, int);
};
