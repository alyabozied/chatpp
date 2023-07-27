
// Server side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <cctype>
#include <string>
#include <vector>
#include <iostream>
#include "ui.hh"
#define PORT 8000
int main(int argc, char const* argv[])
{
    int newSocket;
    std::cout << "wait trying to connect to a client ..."<<std::endl;
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_addr.s_addr = inet_addr("156.213.164.44");
    address.sin_port = htons(PORT);
    fcntl(server_fd, F_SETFL, O_NONBLOCK);// non-blocking socket

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
    // if (bind(server_fd, localaddr->ai_addr, localaddr->ai_addrlen)< 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
        struct sockaddr_in clientAddr;

        // Waiting until client connect
    do
    {
        newSocket = accept(server_fd,(struct sockaddr*)&clientAddr,(socklen_t*)&addrlen);
    } while (newSocket < 0);
    
    UI* myUI = UI::initUI();
    fcntl(newSocket, F_SETFL, O_NONBLOCK);// non-blocking socket
    while(true){
        valread = read(newSocket, buffer, 1024);
        std::string s = myUI->readUserInput();
        if(s.length() >0){
            send(newSocket,s.c_str(),s.length(),0);
            myUI->printMessages(s,1);
        }

        
        if(valread == -1){
            refresh();
            continue;
        }
        if(valread ==0){
            refresh();
            break;
        }
        myUI->printMessages(buffer,2);
    }

  
    // closing the connected socket
    endwin();
    close(newSocket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}