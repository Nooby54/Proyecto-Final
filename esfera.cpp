#include "esfera.h"
#include <QPixmap>
#include <QtMath>

Esfera::Esfera(unsigned char id, qreal x, qreal y) : id(id), recolectada(false), x(x), y(y), fase(0){
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

bool Esfera::estaRecolectada() const {
    return recolectada;
}

void Esfera::recolectar() {
    recolectada = true;
    this->setVisible(false);
    timerMovimiento->stop();
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
    x-=5;
    setPos(x,y);
}
