#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QPixmap>
#include <QObject>
#include <QGraphicsPixmapItem>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    qreal x, y, velX, velY;
    unsigned int dx, dy, contadorSprite, spriteX, spriteY, spriteAncho, spriteAlto;
    QPixmap hojaSprites, sprite;
    QSize limites;
    unsigned char vida;
public:
    Personaje();
    void recibirDanio();
    virtual void configurarSprite(int dir);
    virtual ~Personaje();
};

#endif // PERSONAJE_H
