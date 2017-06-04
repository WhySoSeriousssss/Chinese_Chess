#ifndef CGAME_H
#define CGAME_H

#include "model/CPlayer.h"
#include "model/CMovement.h"
#include "model/CGameInfo.h"
#include "include/pugixml.hpp"
#include "util.h"
#include <vector>
#include <QEventLoop>
#include <QObject>
#include "socket/networkconnect.h"

using namespace std;

class CGame : public QObject {
    Q_OBJECT
public:
/// member functions
    CGame();
    ~CGame();

    void Initialize();

    void Save();
    void Load();

    void SetPieceStatus(int id, bool alive);
    void RefreshPiecesData();
    void ChangeTurn();

    bool PlayerIsInCheck(int player);
    int DetectInCheck();
    int DetectCheckmate();

    vector<CPiece *> GetPiecesRed();
    vector<CPiece *> GetPiecesBlack();

    bool PieceAttemptsToMove(CMovement* move);
    void PieceMove(CMovement* move);

    // Game loop
    void RunLoop();

    void BindNetwork(NetworkConnect *n);

private slots:
    // receive the movement generated from the controller
    void ReceiveMovement(CMovement *movement);

public slots:
    // process the game thread
    void process();

signals:
    void MovementReceived();

    void ChangePiecePosition(CMovement*);

    void RemovePiece(int);

    // game thread is finished
    void finished();

private:
    CMovement *receivedMovement;

    CPlayer* players[2];

    NetworkConnect *network;
};

#endif // CGAME_H
