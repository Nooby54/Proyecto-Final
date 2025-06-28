#include "mainwindow.h"
#include "goku.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, 600, 600);

    Goku* goku = new Goku();
    escena->addItem(goku);
    goku->setPos(200,200);
    goku->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}
