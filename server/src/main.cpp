#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>
#include <sstream>


int process(int socket)
{
    char buff[512];
    while (true)
    {
        
        memset(buff, 0, sizeof(buff));
        std::string message = "";
        int ret = recv(socket, buff, 512, 0);
        if (ret == -1)
        {
            std::cout << "socket error\n";
            return 0;
        }
        else if (ret > 0)
        {
            std::cout << "message : " << std::string(buff) << std::endl;
            std::cout << "right your message : ";
            std::getline(std::cin,message);
            send(socket,message.c_str(), strlen(message.c_str()), 0);
        }
    }
}

int main()
{
    WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		std::cout << "Winsock Connection Failed!" << std::endl;
		exit(1);
	}
    struct addrinfo* result = NULL;
    struct addrinfo hints;

    memset(&hints, 0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(NULL, "5000", &hints, &result) != 0) {
        std::cout << "getaddrinfo failed" << std::endl;
        return 1;
    }
    int serverSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (serverSocket == INVALID_SOCKET) {
        std::cout << "socket failed" << std::endl;
        return 1;
    }


    if (bind(serverSocket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        return 1;
    }


    listen(serverSocket, 1);
    int clientSocket = accept(serverSocket, NULL, NULL);
    process(clientSocket);
    return 0;
}