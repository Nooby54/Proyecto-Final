#include "plataforma.h"
#include "qbrush.h"
#include <QRandomGenerator>

Plataforma::Plataforma() {
    // Mirar si colocar posiciones fijas en algun eje
    x = QRandomGenerator::global()->bounded(0, 1401);
    y = QRandomGenerator::global()->bounded(250, 400);

    setRect(0, 0, 100, 20);
    setBrush(QBrush(Qt::darkGreen));
    setPos(x, y);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Plataforma::mover);
    timerMovimiento->start(20);
}

void Plataforma::mover(){
    x-=5;
    setPos(x,y);
    return;
}
