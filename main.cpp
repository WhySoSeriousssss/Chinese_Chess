#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "QBoard.h"
#include "QPiece.h"
#include "QGameScene.h"
#include "CGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
    CCoordinatesSet set;
    std::cout << set.Size() << "\n";
    set.Add(CCoordinate(1, 2));
    set.Print();

    CPiece p1(3, 4, CHARIOT, RED, 1, 1);

    pBoard->m_iBoard[3][2] = 210;
    pBoard->m_iBoard[5][4] = 211;
    pBoard->m_iBoard[7][4] = 212;

    pBoard->m_iBoard[3][6] = 111;
    pBoard->m_iBoard[3][8] = 110;

    p1.ComputeEffectiveNextMoves();
*/


//    pBoard->Initialize();
//    pBoard->Print();
/*
    QGraphicsScene *scene = new QGraphicsScene;

    scene->setSceneRect(0, 0, 600, 450);
    QPiece *item1 = new QPiece(100, 0, 0, 40);
    QPiece *item2 = new QPiece(100, 0, 1, 40);
    QPiece *item3 = new QPiece(100, 1, 0, 40);

    QString file = "../Chinese_Chess/Images/CANVAS.GIF";
    QBoard *board = new QBoard(file, 377, 417);

    scene->addItem(board);
    item1->setPos(10, 10);
    scene->addItem(item1);
    item2->setPos(50, 50);
    scene->addItem(item2);
    item3->setPos(90, 50);
    scene->addItem(item3);
    */

    return a.exec();
}
