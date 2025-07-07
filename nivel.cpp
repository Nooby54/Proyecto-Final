#include "nivel.h"
#include "ui_mainwindow.h"
#include "plataforma.h"
#include <QRandomGenerator>

Nivel::Nivel(int id) : id(id) {}

void Nivel::iniciarNivel(Ui::MainWindow *ui)
{
    this->escena = ui->graphicsView->scene();

    // Timer para limpiar la escena
    timerEscena = new QTimer(this);
    connect(timerEscena, &QTimer::timeout, this, &Nivel::actualizar);
    timerEscena->start(32);

    // Modo de juego
    if(id == 1){
        ui->vidaEnemigo->setVisible(false);
        ui->vidaGoku->setVisible(false);
        fondo.load(":/sprites/backgrounds/level1.png");
        fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        QGraphicsPixmapItem *fondo1 = new QGraphicsPixmapItem(fondo);

        fondo = fondo.transformed(QTransform().scale(-1, 1));
        QGraphicsPixmapItem *fondo2 = new QGraphicsPixmapItem(fondo);

        fondo1->setPos(0, 0);
        fondo2->setPos(fondo1->pixmap().width(), 0);

        escena->addItem(fondo1);
        escena->addItem(fondo2);

        goku = new Goku(0, 400, ui->graphicsView, enemigos, plataformas,id);
        escena->addItem(goku);
        goku->setFocus();

        // Plataformas
        plataformas[0] = new Plataforma(400, 425);
        escena->addItem(plataformas[0]);
        ultimaXPlataforma = 400;
        for(unsigned char i = 1; i < 8; i++){
            plataformas[i] = new Plataforma(ultimaXPlataforma + 350,QRandomGenerator::global()->bounded(250, 426));
            escena->addItem(plataformas[i]);
            ultimaXPlataforma = ultimaXPlataforma + 400;
        }

        // Esferas
        for(unsigned short int i = 0; i < 7; i++){
            esferas[i] = nullptr;
        }

        connect(goku, &Goku::moverFondo, this, [=](){
            const int velocidadMovimiento = 15;

            fondo1->setX(fondo1->x() - velocidadMovimiento);
            fondo2->setX(fondo2->x() - velocidadMovimiento);

            if (fondo1->x() <= -fondo1->pixmap().width()) {
                fondo1->setX(fondo2->x() + fondo2->pixmap().width());
            }
            if (fondo2->x() <= -fondo2->pixmap().width()) {
                fondo2->setX(fondo1->x() + fondo1->pixmap().width());
            }

            for (auto plataforma : plataformas){
                plataforma->mover();
            }
            for(auto esfera : esferas){
                if(esfera) esfera->mover();
            }
        });

        timerColisionesEsferas = new QTimer(this);
        connect(timerColisionesEsferas, &QTimer::timeout, this, &Nivel::verificarColisionesEsferas);
        timerColisionesEsferas->start(30);
    }
    else if(id == 2){
        fondo.load(":/sprites/backgrounds/level2.png");
        fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(fondo);
        bgImage->setPos(0, 0);
        ui->graphicsView->scene()->addItem(bgImage);

        goku = new Goku(0, 450, ui->graphicsView, enemigos, plataformas,id);
        escena->addItem(goku);
        goku->setFocus();

        Enemigo* enemigo = new Enemigo(1200, 100, proyectiles, goku, [this](Proyectil* p) { eliminarProyectil(p); },id);
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

void Nivel::eliminarProyectil(Proyectil* p) {
    proyectiles.remove(p);
    p->deleteLater();
}

void Nivel::actualizar(){
    escena->update();

    if(id == 1){
        for(auto plataforma : plataformas){
            if (plataforma->getX() + 150 < 0) {
                plataforma->setX(ultimaXPlataforma + 350);
                plataforma->setY(QRandomGenerator::global()->bounded(200, 401));
                plataforma->setPos(plataforma->getX(),plataforma->getY());

                int probabilidad = QRandomGenerator::global()->bounded(0, 100);
                if (contadorEsferas < 7 && probabilidad < 40) {
                    qDebug() << "Esfera" << contadorEsferas;
                    qreal px = plataforma->getX() + 60;
                    qreal py = plataforma->getY() - 40;
                    esferas[contadorEsferas] = new Esfera(contadorEsferas + 1, px, py);
                    escena->addItem(esferas[contadorEsferas]);
                    contadorEsferas++;
                }
            }
            ultimaXPlataforma = plataforma->getX();
        }
    }
}

void Nivel::verificarColisionesEsferas() {
    for (auto esfera : esferas) {
        if (esfera && !esfera->estaRecolectada() && goku->collidesWithItem(esfera)) {
            esfera->recolectar();
            // Añadir terminacion de nivel
        }
    }
}
