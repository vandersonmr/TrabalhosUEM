#include "include/GerenciadorServidores.hpp"


/* For each connection wait for a msg. When it receve a mensage
 * call askToServer and write the result for the client */
void GerenciadorServidores::clientListening(socket_ptr sock){
   try{
      while(true){
         char data[10000];

         boost::system::error_code error;
         size_t length = sock->read_some(boost::asio::buffer(data), error);

         if (error == boost::asio::error::eof)
            break;
         else if (error)
            throw boost::system::system_error(error);

         cout << "Pergunta: " << data << endl;
         string reply = askToServers(string(data)) + "\n";
         cout << "Resposta: " << reply << endl;
         boost::asio::write(*sock, boost::asio::buffer(
                  reply, reply.size()));
      }
   }catch (std::exception& e){
      std::cerr << "Exception: clientListening: " << e.what() << "\n";
   }
}

/* For each client to conect create a Thread to do what was ask by the
 * client */
void GerenciadorServidores::clientManaging
(boost::asio::io_service& io_service,unsigned short port){

   tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
   while(true){
      socket_ptr sock(new tcp::socket(io_service));
      cout << "Esperando conexão..." << endl;
      a.accept(*sock);
      std::thread(boost::bind(&GerenciadorServidores::clientListening,
               this,sock)).detach();
      cout << "Conexão iniciada!" << endl;
   }

}

/* Send msg to server and return the result msg */
string GerenciadorServidores::sendServer(string msg,int port){
   boost::asio::io_service io_service;

   tcp::socket s(io_service);
   tcp::resolver resolver(io_service);
   boost::asio::connect(s, resolver.resolve({"127.0.0.1",
            to_string(port).c_str()}));

   size_t request_length = std::strlen(msg.c_str());
   boost::asio::write(s, boost::asio::buffer(msg.c_str(),
            request_length));

   char reply[10000];
   size_t reply_length = boost::asio::read(s,
         boost::asio::buffer(reply, request_length));

   message_ptr msg_ptr = messageParse(string(reply));
   return string(reply);
}

/* Ask for all server if they have some thing asked by the msg
 * and return the result from the first server to have*/
string GerenciadorServidores::askToServers
(string msg){
   try{
      int size = 3;
      int serverChecked[3] = {1,1,1};
      while(size!=0){
         int serverId = rand() % 3;
         if(serverChecked[serverId] == 1){
            string res = sendServer(msg,8870+serverId);
            if(res != "null"){
               return res;
            }
            serverChecked[serverId] = 0;
            size--;
         }

      }
   }catch (std::exception& e){
      std::cerr << "Exception: askToServers: " << e.what() << "\n";
   }
   return string("null");
}


void GerenciadorServidores::startService(int port){
   try{
      boost::asio::io_service io_service;
      clientManaging(io_service, port);
   }catch (std::exception& e){
      std::cerr << "Exception: startService: " << e.what() << "\n";
   }
}

int main(){
   cout << "Iniciando servidor na porta 8888" << endl;
   GerenciadorServidores geren;
   geren.startService(8888);
   return 0;
}
