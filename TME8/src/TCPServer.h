#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	// a completer
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port);

	// stoppe le serveur
	void stopServer () ;

    void handleclient(pr::Socket sc){
        int i;
        char buf[1024];
        read(sc.getFD(), &i, sizeof(i));
        i *= 2;
        write(sc, buf, sizeof(buf));
        sc.close();
    }

    TCPServer::~TCPServer(){
        for(auto &e : threads) {
            e.join();
        }
    }

    TCPServer::startServer(int port){
        serv = ServerSocket(port);
        if(!serv.isOpen()){
            exit(EXIT_FAILURE);
        }

        while(true){
            cout << "En attente" << endl;
            Socket sc = serv.accept();
            handleClient(sc);
            threads.emplace_back([](Socket sc){
                handleClient(sc);
            }, sc);
        }
    }
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
