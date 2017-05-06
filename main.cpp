#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "view-controller/QBoard.h"
#include "view-controller/QPiece.h"
#include "view-controller/QGameScene.h"
#include "model/CGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
