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
    enemigos.push_back(new Enemigo(1200,100));
    escena->addItem(enemigos[0]);
    enemigos[0]->setPos(1200,100);

    // Goku
    Goku* goku = new Goku(0,450,ui->graphicsView, enemigos);
    escena->addItem(goku);
    goku->setPos(0,450);
    goku->setFocus();

    // Actualizadores de vida
    connect(enemigos[0], &Enemigo::actualizarVida, this, [=](int vida) { ui->vidaEnemigo->setValue(vida);});

    // Diseño barras de vida
    ui->vidaEnemigo->setFixedHeight(30);
    ui->vidaEnemigo->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: purple;}");
    ui->vidaGoku->setFixedHeight(30);
    ui->vidaGoku->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: orange;}");

    // Proyectiles de prueba
    vector<Obstaculo*> proyectiles;
    for(int i = 0; i < 50; i++){
        int velAleatoria = QRandomGenerator::global()->bounded(100, 401);    // 100 a 400
        int anguloAleatorio = QRandomGenerator::global()->bounded(120, 221); // 120 a 220
        int gravedadAleatoria = QRandomGenerator::global()->bounded(30, 51);   // 30 a 50

        proyectiles.push_back(new Obstaculo(velAleatoria, enemigos[0]->pos().x(), enemigos[0]->pos().y() + i * 100, anguloAleatorio, gravedadAleatoria));
        escena->addItem(proyectiles[i]);
        proyectiles[i]->setPos(enemigos[0]->pos().x(), enemigos[0]->pos().y() + i * 100);
        proyectiles[i]->iniMov();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
