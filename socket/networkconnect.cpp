#include "socket/networkconnect.h"

NetworkConnect::NetworkConnect() {
    server = NULL;
    client = NULL;
}

NetworkConnect::~NetworkConnect() {
    delete server;
    delete client;
}

void NetworkConnect::Send(char *data, int datasize) {
    if (isServer == true) {
        send(server->ClientSocket, data, datasize, 0);
    }
    else {
        send(client->ConnectSocket, data, datasize, 0);
    }
}

void NetworkConnect::Receive(char *data, int datasize) {
    if (isServer == true) {
        recv(server->ClientSocket, data, datasize, 0);
    }
    else {
        recv(client->ConnectSocket, data, datasize, 0);
    }
}

bool NetworkConnect::GetIsServer() {
    return isServer;
}

void NetworkConnect::SetAsServer() {
    isServer = true;
    server = new Server();
    server->acceptNewClient();
}

void NetworkConnect::SetAsClient() {
    isServer = false;
    client = new Client();
    client->Connect();
}
