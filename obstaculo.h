#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "goku.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    qreal x, y, velX, velY, angulo, velInicial;
    unsigned int dx, dy, contadorSprite, spriteX, spriteY, spriteAncho=32, spriteAlto=32;
    QPixmap hojaSprites, spriteActual;
private slots:
    void mover(qreal velInicial); // MRUA
    void mover(qreal angulo, qreal velInicial); // Parabolico
public:
    Obstaculo();
    void hacerDanio(Goku* goku);
};

#endif // OBSTACULO_H
