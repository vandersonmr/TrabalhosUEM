#include <boost/thread/thread.hpp>
#include <iostream>
#include "boost/shared_ptr.hpp"
#include "lib/msgParse.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include <boost/ref.hpp>

typedef boost::shared_ptr<Message> message_ptr;
using boost::asio::ip::tcp;
using namespace std;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

class Server{
   private:
      void clientManaging();
      void execMsg(string);
   public:
      void startServer(int);
};
