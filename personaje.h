#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QPixmap>
#include <QObject>
#include <QGraphicsPixmapItem>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    qreal x, y, velX = 0, velY = 0, velInicial, theta;
    unsigned int dx = 0, dy = 0, contadorSprite = 0, spriteX = 0, spriteY = 0, spriteAncho = 0, spriteAlto = 0, contador = 0;
    QPixmap hojaSprites, spriteActual;
    unsigned char vida = 255;
    QTimer *timerMovimiento;
    bool direccion = true;
public:
    Personaje();
    Personaje(unsigned int x, unsigned int y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta);
    void recibirDanio();
    virtual void configurarSprite(int dir);
    virtual ~Personaje();
};

#endif // PERSONAJE_H
