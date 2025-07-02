#include "obstaculo.h"

#include <QTimer>
#include <QDebug>

Obstaculo::Obstaculo(float velIn, qreal xIn, qreal yIn, float theta, unsigned int g)
    : x(xIn), y(yIn), velIn(velIn),xIn(xIn),yIn(yIn),g(g) {
    hojaSprites.load(":/sprites/proyectil (32x32).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, [=]() { movParabolico(); });
    this->theta = qDegreesToRadians(theta);
}

void Obstaculo::iniMov(){
    timerMovimiento->start(50);
}

void Obstaculo::movParabolico()
{
    vX = velIn * cos(theta);
    x = xIn + (vX*tiempo);
    y = yIn + (-velIn * sin(theta) * tiempo) + (0.5 * g * tiempo * tiempo);
    vY = -velIn * sin(theta) + g * tiempo;

    if (x>1400 || x<-32 || y>730){
        timerMovimiento->stop();
    }

    if(y<0){
        velIn = sqrt(vX * vX + vY * vY)*0.8;
        theta = atan2(vY,vX);
        velIn = 0.8*velIn;
        tiempo = 0;
        dirY = y < 0 ? 1 : 0;
        yIn = y - (dirY ? -10 : 10);
        xIn = x;
    }

    setPos(x, y);
    tiempo += 0.1;
}
