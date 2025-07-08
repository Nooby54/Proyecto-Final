#include "esfera.h"
#include <QPixmap>
#include <QtMath>

Esfera::Esfera(unsigned char id, qreal x, qreal y, Goku* goku, Plataforma* plataforma) : id(id), x(x), y(y), goku(goku), plataforma(plataforma){
    hojaSprites.load(":/sprites/Esferas (64x64).png");
    spriteActual = hojaSprites.copy((id-1)*64, 0, 64, 64);
    spriteActual = spriteActual.scaled(32, 32, Qt::KeepAspectRatio);
    setPixmap(spriteActual);

    setPos(x, y);
    yOriginal = y;

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Esfera::moverSenoidal);
    timerMovimiento->start(16);
}

bool Esfera::getRecolectada() {
    return recolectada;
}

void Esfera::moverSenoidal() {
    if (recolectada) return;

    fase += 0.15;
    if (fase > 6.28) fase = 0;

    qreal yOffset = 15 * qSin(fase);
    y = yOriginal + yOffset;
    setY(y);
}

void Esfera::mover(){
    if (!recolectada && goku->collidesWithItem(this)) {
        recolectada = true;
        this->setVisible(false);
        timerMovimiento->stop();
        plataforma->setTieneEsfera(false);
        emit esferaRecolectada();
    }

    if (plataforma) {
        x = plataforma->getX() + 60;
        if(plataforma->getReposicionado()){
            y = plataforma->getY() - 40;
            yOriginal = y;
            plataforma->setReposicionado(false);
        }
    }
    setPos(x, y);
}
