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
    unsigned int dx, dy, contadorSprite, spriteX, spriteY, spriteAncho, spriteAlto;
    QPixmap hojaSprites, sprite;
public:
    Obstaculo();
    void mover(qreal velInicial); // MRUA
    void mover(qreal angulo, qreal velInicial); // Parabolico
    void hacerDanio(Goku* goku);
};

#endif // OBSTACULO_H
