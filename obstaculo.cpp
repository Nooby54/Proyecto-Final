#include "obstaculo.h"
#include "goku.h"
#include <QTimer>

Obstaculo::Obstaculo(Goku* goku, float velInicial, qreal xIn, qreal yIn, float theta, unsigned int g)
    : x(xIn), y(yIn), velInicial(velInicial), xIn(xIn),yIn(yIn),g(g),goku(goku) {
    hojaSprites.load(":/sprites/proyectil (32x32).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, [=]() { movimientoParabolico(); });
    this->theta = qDegreesToRadians(theta);
}

void Obstaculo::mover(){
    timerMovimiento->start(50);
}

void Obstaculo::movimientoParabolico()
{
    vX = velInicial * cos(theta);
    x = xIn + (vX*tiempo);
    y = yIn + (-velInicial * sin(theta) * tiempo) + (0.5 * g * tiempo * tiempo);
    vY = -velInicial * sin(theta) + g * tiempo;

    if (x>1400 || x<-32 || y>730){
        timerMovimiento->stop();
        this->deleteLater();
        return;
    }

    if(y<0){
        velInicial = sqrt(vX * vX + vY * vY)*0.8;
        theta = atan2(vY,vX);
        velInicial *= 0.8;
        tiempo = 0;
        dirY = y < 0 ? 1 : 0;
        yIn = y - (dirY ? -10 : 10);
        xIn = x;
    }

    setPos(x, y);
    tiempo += 0.1;

    if (collidesWithItem(goku)) {
        goku->recibirDanio();
        timerMovimiento->stop();
        this->deleteLater();
        return;
    }
}

