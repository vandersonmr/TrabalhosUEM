#include "../src/include/graph.hpp"
#define BOOST_TEST_MODULE test_graph
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <sstream>

BOOST_AUTO_TEST_CASE(testGraphFileNotExist) {
  BOOST_REQUIRE_THROW(new Graph("../naoExiste.txt"), const char*);
}

BOOST_AUTO_TEST_CASE(testGraphFileExist) {
  BOOST_CHECK_NO_THROW(Graph g("../data/gcol1.txt"));
}

BOOST_AUTO_TEST_CASE(testGraphLoaded) {
  Graph g("../data/gcol1.txt");
  BOOST_CHECK_GE(g.getSize(), 1);
}

BOOST_AUTO_TEST_CASE(testGraphFiles) {
  for(int i = 1; i < 87; i++) {
    std::ostringstream oss;
    oss << "../data/" << i << ".txt";
    Graph* g;
    BOOST_CHECK_NO_THROW(new Graph(oss.str()));
    g = new Graph(oss.str());
    BOOST_CHECK_GE(g->getSize(), 1);
    delete g;
  }
}

BOOST_AUTO_TEST_CASE(testVertexs) {
  Graph g("../data/gcol1.txt");
  for(int i = 1; i < g.getSize(); i++)
    BOOST_CHECK_NO_THROW(g.getVertex(i));
  BOOST_REQUIRE_THROW(g.getVertex(0), const char*);
  BOOST_REQUIRE_THROW(g.getVertex(g.getSize()+1), const char*);
}

BOOST_AUTO_TEST_CASE(testEdges) {
  Graph g("../data/gcol1.txt");
  auto v = g.getVertex(1);
  vector<int> e = v->getEdges();
  BOOST_CHECK(e.size() > 0);
  for(int i : e)
    BOOST_CHECK_GE(i, 2);
}

BOOST_AUTO_TEST_CASE(testRandomWeight) {
  Graph g("../data/gcol1.txt");
  for(int i = 1; i < g.getSize(); i++) 
    BOOST_CHECK_GE(g.getVertex(i)->getWeight(), 1);
}

