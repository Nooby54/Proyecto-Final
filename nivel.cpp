#include "nivel.h"
#include "ui_mainwindow.h"

Nivel::Nivel(int id) : id(id) {}

void Nivel::iniciarNivel(Ui::MainWindow *ui)
{
    this->escena = ui->graphicsView->scene();
    if(id == 1){
        return;
    }
    else if(id == 2){
        QPixmap backgroundImage(":/sprites/backgrounds/level2.png");
        backgroundImage = backgroundImage.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(backgroundImage);
        bgImage->setPos(0, 0);
        ui->graphicsView->scene()->addItem(bgImage);

        goku = new Goku(0, 450, ui->graphicsView, enemigos);
        goku->setPos(0, 450);
        escena->addItem(goku);
        goku->setFocus();

        Enemigo* enemigo = new Enemigo(1200, 100, proyectiles, goku);
        enemigo->setPos(1200, 100);
        escena->addItem(enemigo);
        enemigos.push_back(enemigo);

        connect(enemigos[0], &Enemigo::actualizarVida, this, [=](int vida) {ui->vidaEnemigo->setValue(vida);});
        connect(goku, &Goku::actualizarVida, this, [=](int vida) {ui->vidaGoku->setValue(vida);});
    }
    else{
        ui->vidaEnemigo->setVisible(false);
        ui->vidaGoku->setVisible(false);
        QPixmap backgroundImage(":/sprites/backgrounds/level1.png");
        backgroundImage = backgroundImage.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(backgroundImage);
        bgImage->setPos(0, 0);
        escena->addItem(bgImage);
    }
}
