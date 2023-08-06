#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

class NetworkAdapter{
    struct sockaddr_in address;
    int newSocket,server_fd, opt = 1,addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    static NetworkAdapter* networkAdapter;
    NetworkAdapter(std::string clientOrServer,std::string ipaddress);
    NetworkAdapter(NetworkAdapter const&);
    void operator=(NetworkAdapter const &);
    void __initclient(std::string ipaddress);
    void __initserver();
    public:
        static NetworkAdapter*initNetworkAdpater(std::string clientOrServer = "client" ,std::string ipaddress = "127.0.0.1");
        void sendMessage(std::string s);
        int receiveMessage(char*buffer,int bufferLen);
        ~NetworkAdapter();

};