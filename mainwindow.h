#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtGui>
#include "view-controller/QGameScene.h"
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void IntializeScene();
    ~MainWindow();

    QGameScene *gameScene;

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
