#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameScene = new QGameScene();

    QGraphicsView *view = new QGraphicsView;
    view->setScene(gameScene);
    //view->show();

    setCentralWidget(view);

    setFixedSize(650, 432);
    setStatusBar(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IntializeScene() {
    gameScene->Initialize();
}

void MainWindow::paintEvent(QPaintEvent *)
{


}

