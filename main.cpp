#include "socket/networkconnect.h"
#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include "model/CGame.h"
#include <QDebug>
#include <stdio.h>
#include <QThread>
#include "networkconnectdialog.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // network creation dialog
    NetworkConnectDialog *dlg = new NetworkConnectDialog();
    NetworkConnect *nc = new NetworkConnect();

    QObject::connect(dlg, SIGNAL(JoinButtonReleased()), nc, SLOT(SetAsClient()));
    QObject::connect(dlg, SIGNAL(CreateButtonReleased()), nc, SLOT(SetAsServer()));
    dlg->exec();


    // create and initialize the game core thread
    QThread *gameThread = new QThread;
    CGame *game = new CGame();

    QObject::connect(gameThread, SIGNAL(started()), game, SLOT(process()));
    QObject::connect(game, SIGNAL(finished()), gameThread, SLOT(quit()));
    QObject::connect(game, SIGNAL(finished()), game, SLOT(deleteLater()));
    QObject::connect(gameThread, SIGNAL(finished()), gameThread, SLOT(deleteLater()));

    game->Initialize();
    game->BindNetwork(nc);

    // create the main GUI, set up signals & slots connection between game and scene
    MainWindow w;
    QObject::connect(w.gameScene, SIGNAL(SendMovement(CMovement*)), game, SLOT(ReceiveMovement(CMovement*)));
    QObject::connect(game, SIGNAL(ChangePiecePosition(CMovement*)), w.gameScene, SLOT(ChangePiecePosition(CMovement*)));
    QObject::connect(game, SIGNAL(RemovePiece(int)), w.gameScene, SLOT(RemovePiece(int)));

    w.gameScene->SetPiecesReference(game->GetPiecesRed(), game->GetPiecesBlack());
    w.gameScene->Initialize();
    w.show();

    // start the game core thread
    game->moveToThread(gameThread);
    nc->moveToThread(gameThread);
    gameThread->start();


    return a.exec();
}
