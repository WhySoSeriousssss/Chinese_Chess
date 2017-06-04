#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "6666"

class Server {
public:
    Server();
    ~Server();

    // accept new connections
    bool acceptNewClient();

    int iResult;

    SOCKET ListenSocket;
    SOCKET ClientSocket;
};

#endif

