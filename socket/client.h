#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>

#define DEFAULT_PORT "6666"

#pragma comment(lib, "Ws2_32.lib")

class Client {
public:
    Client();
    ~Client();

    void Connect();
    int iResult;

    // socket for client to connect to server
    SOCKET ConnectSocket;
};

#endif
