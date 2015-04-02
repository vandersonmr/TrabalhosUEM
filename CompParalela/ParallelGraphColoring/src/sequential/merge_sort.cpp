#include "include/merge_sort_sequential.hpp"

vector<Vertex> MergeSortSequential::mergeSort(vector<Vertex>& vec) {
  if(vec.size() == 1)
    return vec;

  std::vector<Vertex>::iterator middle = vec.begin() + (vec.size() / 2);

  vector<Vertex> left(vec.begin(), middle);
  vector<Vertex> right(middle, vec.end());

  left  = mergeSort(left);
  right = mergeSort(right);

  return merge(left, right);
}
