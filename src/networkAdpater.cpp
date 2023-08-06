#include "networkAdpater.hh"
#define PORT 8000

NetworkAdapter* NetworkAdapter::networkAdapter = nullptr;
void NetworkAdapter::__initserver(){
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
    address.sin_addr.s_addr = inet_addr("0.0.0.0");
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

    do
    {
        newSocket = accept(server_fd,(struct sockaddr*)&clientAddr,(socklen_t*)&addrlen);
    } while (newSocket < 0);
        
    fcntl(newSocket, F_SETFL, O_NONBLOCK);// non-blocking socket

  
}
void NetworkAdapter::__initclient(std::string ipaddress){

    
    if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        
        perror(" Socket creation error");
        exit(EXIT_FAILURE);
    }
    fcntl(newSocket, F_SETFL, O_NONBLOCK);

    address.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    address.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET,ipaddress.c_str(), &address.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    //connect to server
    int status = -1;
    do {
    status = connect(newSocket,(struct sockaddr*)&address,sizeof(address));

    }while(status <0);
}
NetworkAdapter::NetworkAdapter(std::string clientOrServer,std::string ipaddress){
    if (clientOrServer == "server")
        __initserver();
    else 
        __initclient(ipaddress);
    
}

NetworkAdapter* NetworkAdapter::initNetworkAdpater(std::string clientOrServer,std::string ipaddress){
    if(networkAdapter == nullptr){
        networkAdapter = new NetworkAdapter(clientOrServer,ipaddress);
    }
    return networkAdapter;
    
}

void NetworkAdapter::sendMessage(std::string s){
    send(newSocket,s.c_str(),s.length(),0);
}
int NetworkAdapter::receiveMessage(char*buffer,int bufferLen){
    return read(newSocket, buffer, 1024);
}

NetworkAdapter::~NetworkAdapter(){
    close(newSocket);
    shutdown(server_fd, SHUT_RDWR);
}