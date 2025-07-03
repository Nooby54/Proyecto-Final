#include "mainwindow.h"
#include "enemigo.h"
#include "goku.h"
#include "obstaculo.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, 600, 600);

    QPixmap backgroundImage("../../sprites/backgrounds/nivel1.png");
    QPixmap scaledBackground = backgroundImage.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(scaledBackground);
    bgImage->setPos(0, 0);
    escena->addItem(bgImage);

    // Tamaños de ventana
    ui->graphicsView->scene()->setSceneRect(0, 0, 1400, 730);
    ui->graphicsView->setFixedSize(1400, 730);
    this->setFixedSize(1426, 756);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Goku
    Goku* goku = new Goku(0,450,ui->graphicsView, enemigos);
    escena->addItem(goku);
    goku->setPos(0,450);
    goku->setFocus();

    // Enemigo
    enemigos.push_back(new Enemigo(1200,100, proyectiles,goku));
    escena->addItem(enemigos[0]);
    enemigos[0]->setPos(1200,100);

    // Actualizadores de vida
    connect(enemigos[0], &Enemigo::actualizarVida, this, [=](int vida) { ui->vidaEnemigo->setValue(vida);});
    connect(goku, &Goku::actualizarVida, this, [=](int vida) { ui->vidaGoku->setValue(vida);});

    // Diseño barras de vida
    ui->vidaEnemigo->setFixedHeight(30);
    ui->vidaEnemigo->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: purple;}");
    ui->vidaGoku->setFixedHeight(30);
    ui->vidaGoku->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: orange;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}
