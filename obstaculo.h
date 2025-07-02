#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "goku.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Obstaculo(QGraphicsView *view, float velIn,qreal xIn, qreal yIn, float theta);

    void moveBy(int dx, int dy);
    void movParabolico(float* dt);
    void iniMov();

private:
    qreal x, y, velX, velY, angulo, velInicial;
    unsigned int dx, dy, contadorSprite, spriteX, spriteY, spriteAncho=32, spriteAlto=32;
    QPixmap hojaSprites, spriteActual;

    qreal posX,posY,velIn,theta,dirX,dirY,xIn,yIn,tiempo;
    QSize viewRect;
    QTimer *timerMovPar;


private slots:
    void movParabolico();
};

#endif // OBSTACULO_H
