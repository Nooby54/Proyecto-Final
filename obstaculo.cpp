#include "obstaculo.h"

#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>

#define PI 3.14159265

Obstaculo::Obstaculo(QGraphicsView *view, float velIn, qreal xIn, qreal yIn, float theta)
    : posX(xIn), posY(yIn), velIn(velIn),xIn(xIn),yIn(yIn){
    hojaSprites.load(":/sprites/proyectil (32x32).png");
    spriteX = 0;
    spriteY = 0;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    viewRect = view->size();
    dirX = 1;
    dirY = 1;
    tiempo = 0;
    timerMovPar = new QTimer(this);
    connect(timerMovPar, &QTimer::timeout, this, [=]() {movParabolico();});
    this->theta = qDegreesToRadians(theta);
}

void Obstaculo::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}


void Obstaculo::iniMov(){
    if(timerMovPar->isActive()){
        timerMovPar->stop();
    }else{timerMovPar->start(50);}
}

void Obstaculo::movParabolico()
{
    posX = xIn + (velIn * cos(theta) * tiempo);
    posY = yIn + (-velIn * sin(theta) * tiempo) + (0.5 * 9.8 * tiempo * tiempo);
    velX = velIn * cos(theta);
    velY = -velIn * sin(theta) + 9.8 * tiempo;
    //qDebug() << sin(theta)<<posY<<theta<<velIn<<velY<<velX;

    if (posX>viewRect.width()-30||posX<0){
        velIn = sqrt(velX * velX + velY * velY)*0.8;
        dirX = -1*dirX;
        xIn = posX + 10*dirX;
        tiempo = 0;
        yIn = posY;
        theta = 180*PI/180 + atan2(velY,velX);
        //qDebug()<<"Choque en x" <<xIn<<viewRect.width()<<theta<<posY<<atan2(velY,velX);
    }
    if (posY>viewRect.height()-30||posY<0){
        velIn = sqrt(velX * velX + velY * velY)*0.8;
        theta = atan2(velY,velX);
        //qDebug()<<"Choque en Y"<<atan2(velY,velX)<<cos(theta);
        velIn = 0.8*velIn;
        tiempo = 0;
        if(posY<0){
            dirY = -1;}
        else{dirY = 1;}
        yIn = posY-10*dirY;
        xIn = posX;
    }

    setPos(posX, posY);
    tiempo += 0.2;
}
