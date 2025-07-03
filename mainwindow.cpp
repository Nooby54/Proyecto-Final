#include "mainwindow.h"
#include "nivel.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, 1400, 730);

    ui->graphicsView->scene()->setSceneRect(0, 0, 1400, 730);
    ui->graphicsView->setFixedSize(1400, 730);
    this->setFixedSize(1426, 756);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Nivel 2, de prueba
    nivel = new Nivel(2);
    nivel->iniciarNivel(ui);

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
