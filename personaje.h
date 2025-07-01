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
    unsigned int dx = 0, dy = 0, contadorSprite = 0, spriteX = 0, spriteY = 0, spriteAncho = 0, spriteAlto = 0;
    QPixmap hojaSprites, spriteActual;
    unsigned char vida = 255;
    QTimer *timerMovimiento;
    bool direccion = true;
signals:
    void actualizarVida(unsigned char vida);
public:
    Personaje();
    Personaje(unsigned int x, unsigned int y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta);
    virtual void recibirDanio();
    virtual void configurarSprite(unsigned char dir);
    virtual ~Personaje();
};

#endif // PERSONAJE_H
