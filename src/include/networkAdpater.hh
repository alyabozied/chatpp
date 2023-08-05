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
    NetworkAdapter();
    NetworkAdapter(NetworkAdapter const&);
    void operator=(NetworkAdapter const &);
    public:
        static NetworkAdapter*initNetworkAdpater();
        void sendMessage(std::string s);
        int receiveMessage(char*buffer,int bufferLen);
        ~NetworkAdapter();

};