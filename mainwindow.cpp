#include "mainwindow.h"
#include "enemigo.h"
#include "goku.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, 600, 600);

    // Tamaños de ventana
    ui->graphicsView->scene()->setSceneRect(0, 0, 1400, 730);
    ui->graphicsView->setFixedSize(1400, 730);
    this->setFixedSize(1426, 756);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Goku* goku = new Goku(0,450,ui->graphicsView);
    escena->addItem(goku);
    goku->setPos(0,450);
    goku->setFocus();

    Enemigo* piccolo = new Enemigo(1200,0);
    escena->addItem(piccolo);
    piccolo->setPos(1200,0);

}

MainWindow::~MainWindow()
{
    delete ui;
}
