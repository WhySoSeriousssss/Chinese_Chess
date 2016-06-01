#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGameScene *scene = new QGameScene;
    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    //view->show();

    setCentralWidget(view);

    setFixedSize(650, 432);
    setStatusBar(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{


}

