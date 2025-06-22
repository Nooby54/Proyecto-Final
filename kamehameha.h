#ifndef KAMEHAMEHA_H
#define KAMEHAMEHA_H

#include "enemigo.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Kamehameha: public QObject, public QGraphicsPixmapItem
{
private:
    qreal x, y, velX, velY;
    unsigned int dx, dy, contadorSprite, spriteX, spriteY, spriteAncho, spriteAlto;
    QPixmap hojaSprites, sprite;
public:
    Kamehameha();
    void lanzar();
    void hacerDanio(Enemigo* enemigo);
};

#endif // KAMEHAMEHA_H
