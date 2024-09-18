#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <sstream>


int main() {
    WSAData wsaData;
    char buff[512];
    char* initial_message = "hello";
    std::string chat_message = "";


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    const char* server_address = "127.0.0.1";
    const char* port = "5000";

    struct addrinfo *result=NULL,*ptr=NULL,hints;
    memset(&hints, 0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if(getaddrinfo(server_address,port,&hints,&result) != 0)
    {
        std::cout << "failed"<<std::endl;
        return 1;
    }

    int clientSocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol);

    if(connect(clientSocket,result->ai_addr,(int)result->ai_addrlen) == SOCKET_ERROR)
    {
       std::cout << "connection failed" << std::endl;
    }

    int sendResult = send(clientSocket,initial_message,strlen(initial_message),0);
    
    while(true)
    {
        memset(buff, 0, sizeof(buff));
        int ret = recv(clientSocket,buff,512,0);
        if (ret == -1)
        {
            std::cout << "socket error\n";
            return 0;
        }
        else if (ret > 0)
        {
            std::cout << "message : " << std::string(buff) << std::endl;
            std::cout << "right your message : ";
            std::getline(std::cin,chat_message);
            int sendResult = send(clientSocket,chat_message.c_str(),strlen(chat_message.c_str()),0);
        }
        
    }

    return 0;
}   