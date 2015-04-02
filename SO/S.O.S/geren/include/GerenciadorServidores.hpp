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

using boost::asio::ip::tcp;
using namespace std;
typedef boost::shared_ptr<tcp::socket> socket_ptr;
typedef boost::shared_ptr<Message> message_ptr;

class GerenciadorServidores{
   private:
      void clientListening(socket_ptr);
      void serverManaging();
      string sendServer(string,int);
      void clientManaging(boost::asio::io_service& io_service, unsigned short port);
      string askToServers(string);
   public:
      void startService(int port);
};
