#include "include/Server.hpp"

//!TODO
/*
 * Aqui tem que ter o sistema de comunicação entre os dois
 * forks!
 */

/* TODO depois de receber uma mensagem tem que colocar na fila
 * para que o outro fork fique consumindo.*/
void Server::clientManaging(){
   /* TODO Só copiar o código do gerenciador. Pra cada conexão criar uma thread.
    * Recebeu uma mensagem coloca na fila.*/

}

void Server::execMsg(string msg){
   /*!TODO
    * Executa a mensagem e envia o resultado.
    */
}

void Server::startServer(int port){
   int id = fork();
   if(id == 0){
      try{
         boost::asio::io_service io_service;
         //clientManaging(io_service, port);
      }catch (std::exception& e){
         std::cerr << "Exception: startService: " << e.what() << "\n";
      }
   }else{
      /* TODO segundo fork tem que ficar consumindo a fila! */
   }
}

int main(int argc, char *argv[]){
   int port = 0;
   if(argc > 1){
      port = atoi(argv[1]);
   }

   Server server;
   server.startServer(port);
   return 0;
}
