#include "include/merge_sort_parallel.hpp"
#include <omp.h>

vector<Vertex> MergeSortParallel::mergeSortParallel(vector<Vertex>& vec, int threads) {
  if(vec.size() == 1)
    return vec;

  std::vector<Vertex>::iterator middle = vec.begin() + (vec.size() / 2);

  vector<Vertex> left(vec.begin(), middle);
  vector<Vertex> right(middle, vec.end());

  if(threads > 1){
    #pragma omp parallel sections
    {
      #pragma omp section
      {
        left  = mergeSortParallel(left, threads/2);
      }
      #pragma omp section
      {
        right = mergeSortParallel(right, threads - threads/2);
      }
    }
  } else { 
    left = mergeSortParallel(left, 1);
    right = mergeSortParallel(right, 1); 
  } 

  return merge(left, right);
}

vector<Vertex> MergeSortParallel::mergeSort(vector<Vertex>& vec) {
  omp_set_nested(1);
  return mergeSortParallel(vec,4);
}
