
// Client side C/C++ program to demonstrate Socket
// programming
#include <string>
#include "ui.hh"
#include "networkAdpater.hh"
#include <iostream>
#define PORT 8000
  
int main(int argc, char const* argv[])
{
    std::string ipaddress = "127.0.0.1";
    if (argc >1)
        ipaddress = argv[1];
    NetworkAdapter * myNetworkAdapter = NetworkAdapter::initNetworkAdpater("client", ipaddress);       
    std::cout<<"trying to connect to the server ..." << std::endl;
    UI* myUI = UI::initUI();
   int valread;
    char incomingMessage[1024]= {0};
    while(true){
        valread = myNetworkAdapter->receiveMessage(incomingMessage,1024);
        //handle input data from user
        std::string sentMessage = myUI->readUserInput();
        if(sentMessage.length() >0){
            myNetworkAdapter->sendMessage(sentMessage);
            myUI->printMessages(sentMessage,1);
        }        

        if(valread == -1){ // no data 
            refresh();
            continue;
        }
        if(valread ==0){ // client DC'ed
            refresh();
            break;
        }
        // print incoming messages 
        myUI->printMessages(incomingMessage,2);
    }
    delete myUI;
    delete myNetworkAdapter;
    return 0;
}