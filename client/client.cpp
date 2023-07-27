
// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <fcntl.h>
#include <ncurses.h>
#include <string>
#include "ui.hh"
#include <iostream>
#define PORT 8000
  
int main(int argc, char const* argv[])
{
    
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    std::cout<<"trying to connect to the server ..." << std::endl;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    fcntl(client_fd, F_SETFL, O_NONBLOCK);

    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Addre   ss not supported \n");
        return -1;
    }
        std::cout<<"trying to connect to the server ..." << std::endl;

    //connect to server
    do {
    status = connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    }while(status <0);
    char c;
    UI* myUI = UI::initUI();
    while(true){
        valread = read(client_fd, buffer, 1024);
        std::string s = myUI->readUserInput();
        if(s.length() >0){
            send(client_fd,s.c_str(),s.length(),0);
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
    close(client_fd);
    return 0;
}