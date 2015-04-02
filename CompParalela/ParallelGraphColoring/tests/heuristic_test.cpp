#define private public
#define protected public
#include "../src/include/heuristic.hpp"
#include "../src/sequential/include/heuristic.hpp"
#include "../src/parallel/include/heuristic.hpp"
#include "../src/sequential/include/merge_sort_sequential.hpp"
#define BOOST_TEST_MODULE heuristic_test
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <ctime>

BOOST_AUTO_TEST_CASE(testHeuristicSequential) {
  for(int i =1; i < 87; i++){

    ostringstream oss;
    oss << "../data/" << i << ".txt";
    Graph g(oss.str());
    ColorGraphHeuristicSequential alg;
    alg.colour(&g);
    
    for(auto vertex : g.getVertexs()) {
      bool isDiferent = true;
    
      for(auto neighbour : vertex.getEdges()) {
        if(g.getVertex(neighbour)->getColor() == vertex.getColor()) {
         isDiferent = false;
       }
      }
      BOOST_CHECK(isDiferent);
    }
  }
}

BOOST_AUTO_TEST_CASE(testHeuristicParallel) {
  for(int i =1; i < 87; i++){
    ostringstream oss;
    oss << "../data/" << i << ".txt";
    Graph g(oss.str());
    ColorGraphHeuristicParallel alg;
    alg.colour(&g);

    for(auto vertex : g.getVertexs()) {
      bool isDiferent = true;
    
      for(auto neighbour : vertex.getEdges()) {
        if(g.getVertex(neighbour)->getColor() == vertex.getColor()) {
          isDiferent = false;
        }
      }
      BOOST_CHECK(isDiferent);
    }
  }
}


BOOST_AUTO_TEST_CASE(testGetAllNeighboursColors) {
  Graph g("../data/gcol1.txt");
  ColorGraphHeuristic heuristic;
  auto v = g.getVertex(1);
  vector<int> colors = heuristic.getAllNeighboursColors(&g,v);
  BOOST_CHECK_EQUAL(colors.size(),0);

  auto v1 = g.getVertex(5);
  v1->setColor(1);
  BOOST_CHECK_EQUAL(g.getVertex(5)->getColor(),1);

  vector<int> colors2 = heuristic.getAllNeighboursColors(&g,v);
  BOOST_CHECK_EQUAL(colors2.size(),1);
}

BOOST_AUTO_TEST_CASE(testMinimumColorNotIn) {
  Graph g("../data/gcol1.txt");
  ColorGraphHeuristic heuristic;

  auto v1 = g.getVertex(5);
  v1->setColor(2);

  vector<int> colors = heuristic.getAllNeighboursColors(&g, g.getVertex(1));
  BOOST_CHECK_EQUAL(heuristic.minimumColorNotIn(colors),1);

  v1->setColor(1);
  colors = heuristic.getAllNeighboursColors(&g, g.getVertex(1));
  BOOST_CHECK_EQUAL(heuristic.minimumColorNotIn(colors),2);
}

BOOST_AUTO_TEST_CASE(testGetMaximumInNeighbours) {
  Graph g("../data/gcol1.txt");
  ColorGraphHeuristicSequential heuristic;

  list<Vertex> U = heuristic.getSortedListOfVertex(&g);

  BOOST_CHECK(U.size() == g.getVertexs().size());
  BOOST_CHECK(U.size() == (unsigned) g.getSize());
  BOOST_CHECK(U.size() == 100);

  list<Vertex> I = heuristic.getMaximumInNeighbours(&g, U);

  for(auto i : I) {
    for(auto neighbours : i.getEdges()) 
      BOOST_CHECK_GE(i.getDegree(), g.getVertex(neighbours)->getDegree());
  }
}

BOOST_AUTO_TEST_CASE(testRemoveFrom) {
  Graph g("../data/gcol1.txt");
  ColorGraphHeuristicSequential heuristic;

  list<Vertex> U = heuristic.getSortedListOfVertex(&g);
  list<Vertex> I = heuristic.getMaximumInNeighbours(&g, U);

  int size = U.size();

  U = heuristic.removeFrom(U,I);
  for(auto u : U) {
    for(auto i : I) {
      if(u.getId() == i.getId())
        cout << u.getId() << " " <<i.getId() << endl;
      BOOST_CHECK(u.getId() != i.getId());
    }
  }
  BOOST_CHECK((size - I.size()) == U.size());
}
