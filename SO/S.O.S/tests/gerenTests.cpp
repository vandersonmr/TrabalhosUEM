#define BOOST_TEST_MODULE gerenTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "lib/msgParse.hpp"

BOOST_AUTO_TEST_CASE(TestMsgParse){
   message_ptr msg_ptr =
                  messageParse(string("teste?teste1=test"));
   BOOST_CHECK_EQUAL(msg_ptr->reason,string("teste"));
   BOOST_CHECK_EQUAL(msg_ptr->atributes[string("teste1")],
                     string("test"));
}
