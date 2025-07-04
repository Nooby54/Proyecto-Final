#include "nivel.h"
#include "ui_mainwindow.h"

Nivel::Nivel(int id) : id(id) {}

void Nivel::iniciarNivel(Ui::MainWindow *ui)
{
    this->escena = ui->graphicsView->scene();

    // Timer para limpiar la escena
    timerEscena = new QTimer(this);
    connect(timerEscena, &QTimer::timeout, this, [this]() {
        escena->update();
    });
    timerEscena->start(1000);

    // Modo de juego
    if(id == 1){
        ui->vidaEnemigo->setVisible(false);
        ui->vidaGoku->setVisible(false);
        QPixmap fondo(":/sprites/backgrounds/level1.png");
        fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QGraphicsPixmapItem *fondo1 = new QGraphicsPixmapItem(fondo);

        //fondo = fondo.transformed(QTransform().scale(-1, 1)); // Reflejar fondo
        QGraphicsPixmapItem *fondo2 = new QGraphicsPixmapItem(fondo);

        fondo1->setPos(0, 0);
        fondo2->setPos(fondo1->pixmap().width(), 0);

        escena->addItem(fondo1);
        escena->addItem(fondo2);

        QTimer* timerFondo = new QTimer(this);
        connect(timerFondo, &QTimer::timeout, this, [=]() {
            const int velocidadMovimiento = 2;

            fondo1->setX(fondo1->x() - velocidadMovimiento);
            fondo2->setX(fondo2->x() - velocidadMovimiento);

            if (fondo1->x() <= -fondo1->pixmap().width()) {
                fondo1->setX(fondo2->x() + fondo2->pixmap().width());
            }
            if (fondo2->x() <= -fondo2->pixmap().width()) {
                fondo2->setX(fondo1->x() + fondo1->pixmap().width());
            }
        });

        timerFondo->start(15);
    }
    else if(id == 2){
        QPixmap fondo(":/sprites/backgrounds/level2.png");
        fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(fondo);
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
        connect(goku, &Goku::derrotado, this, &Nivel::finalizarNivel);
    }
    else{
        return;
    }
}

void Nivel::finalizarNivel() {
    for (auto proyectil : proyectiles) {
        if (proyectil && escena->items().contains(proyectil)) {
            escena->removeItem(proyectil);
            proyectil->deleteLater();
        }
    }
    proyectiles.clear();

    for (auto enemigo : enemigos) {
        if (enemigo && escena->items().contains(enemigo)) {
            escena->removeItem(enemigo);
            enemigo->deleteLater();
        }
    }
    enemigos.clear();

    if (goku && escena->items().contains(goku)) {
        escena->removeItem(goku);
        goku->deleteLater();
        goku = nullptr;
    }

    for (auto item : escena->items()) {
        if (item && item->scene() == escena) {
            escena->removeItem(item);
        }
    }
}
