
// Server side C/C++ program to demonstrate Socket
// programming
#include <string>
#include <iostream>
#include "ui.hh"
#include "networkAdpater.hh"
int main(int argc, char const* argv[])
{
    std::cout << "wait trying to connect to a client ..."<<std::endl;
    NetworkAdapter * myNetworkAdapter = NetworkAdapter::initNetworkAdpater("server");       
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