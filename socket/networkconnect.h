#ifndef NETWORKCONNECT_H
#define NETWORKCONNECT_H

#include "socket/client.h"
#include "socket/server.h"
#include <QObject>

class NetworkConnect : public QObject {
    Q_OBJECT
public:
    NetworkConnect();
    ~NetworkConnect();

    void Send(char *data, int datasize);
    void Receive(char *data, int datasize);

    bool GetIsServer();

    void IntializeGame();

private slots:
    void SetAsClient();
    void SetAsServer();

private:
    bool isServer;

    Server *server;
    Client *client;

};

#endif // NETWORKCONNECT_H
