#include "include/merge_sort.hpp"

vector<Vertex> MergeSort::merge(const vector<Vertex>& left, const vector<Vertex>& right) {
  vector<Vertex> result;
  unsigned left_it = 0, right_it = 0;

  while(left_it < left.size() && right_it < right.size()) {
    if(left[left_it].getWeight() < right[right_it].getWeight()) {
      result.push_back(left[left_it]);
      left_it++;
    } else {
      result.push_back(right[right_it]);
      right_it++;
    }
  }

  while(left_it < left.size()) {
    result.push_back(left[left_it]);
    left_it++;
  }

  while(right_it < right.size()) {
    result.push_back(right[right_it]);
    right_it++;
  }

  return result;
}


vector<Vertex> MergeSort::sort(vector<Vertex>& disorderly) {
  return mergeSort(disorderly);
}
