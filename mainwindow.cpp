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
    enemigos.push_back(new Enemigo(1200,100));
    escena->addItem(enemigos[0]);
    enemigos[0]->setPos(1200,100);

    Goku* goku = new Goku(0,450,ui->graphicsView, enemigos);
    escena->addItem(goku);
    goku->setPos(0,450);
    goku->setFocus();

    connect(enemigos[0], &Enemigo::actualizarVida, this, [=](int vida)
            { ui->vidaEnemigo->setValue(vida);});

    ui->vidaEnemigo->setFixedHeight(30);
    ui->vidaEnemigo->setStyleSheet("QProgressBar { background: transparent; border: none; }" "QProgressBar::chunk { background-color: purple; }");

    ui->vidaGoku->setFixedHeight(30);
    ui->vidaGoku->setStyleSheet("QProgressBar { background: transparent; border: none; }" "QProgressBar::chunk { background-color: orange; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}
