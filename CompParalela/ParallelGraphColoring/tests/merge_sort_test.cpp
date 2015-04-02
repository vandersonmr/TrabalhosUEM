#include "../src/include/merge_sort.hpp"
#include "../src/sequential/include/merge_sort_sequential.hpp"
#include "../src/parallel/include/merge_sort_parallel.hpp"
#include "../src/include/graph.hpp"
#define BOOST_TEST_MODULE test_merge_sort
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE(testMergeSortSequential) {
  MergeSortSequential mergeSort;

  vector<Vertex> v(1000000);
  for (int i=0; i<1000000; ++i) 
    v[i].setWeight((i * i) % 1000000);
  
  v = mergeSort.sort(v);
  for (int i=0; i<((signed)v.size()-1); ++i)
    BOOST_CHECK_GE(v[i+1].getWeight(), v[i].getWeight());
}

BOOST_AUTO_TEST_CASE(testMergeSortParallel) {
  MergeSortParallel mergeSort;

  vector<Vertex> v(1000000);
  for (int i=0; i<1000000; ++i)
    v[i].setWeight((i * i) % 1000000);
  v = mergeSort.sort(v);
  for (int i=0; i<((signed)v.size()-1); ++i)
    BOOST_CHECK_GE(v[i+1].getWeight(), v[i].getWeight());
}

BOOST_AUTO_TEST_CASE(testMergeSortGraph) {
  MergeSortParallel mergeSort;
  Graph g("../data/gcol1.txt");
  vector<Vertex> v = g.getVertexs();
  v = mergeSort.sort(v);
  for (int i=0; i<((signed)v.size()-1); ++i)
    BOOST_CHECK_GE(v[i+1].getWeight(), v[i].getWeight());
}
