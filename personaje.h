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
    unsigned int contadorSprite = 0, spriteX = 0, spriteY = 0, spriteAncho = 0, spriteAlto = 0;
    QPixmap hojaSprites, spriteActual;
    signed short int vida = 255;
    QTimer *timerMovimiento;
    bool direccion = true;
    unsigned char nivel;

signals:
    void actualizarVida(unsigned char vida);
    void derrotado();

public:
    Personaje(qreal x, qreal y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta, unsigned char nivel);

    qreal getVelY();
    void setVelY(qreal velY);
    void setY(qreal y);
    void setVelX(qreal velX);
    qreal getY();
    virtual void recibirDanio();
    virtual void configurarSprite(unsigned char dir);
    virtual ~Personaje();
};

#endif // PERSONAJE_H
