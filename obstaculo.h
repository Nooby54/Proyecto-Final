#ifndef OBSTACULO_H
#define OBSTACULO_H

class Goku;

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Obstaculo(Goku* goku, float velIn,qreal xIn, qreal yIn, float theta, unsigned int g);
    void movimientoParabolico(float* dt);
    void mover();

private:
    qreal x, y, vX, vY, angulo, velInicial, theta, xIn, yIn, tiempo=0;
    unsigned int dx, dy, contadorSprite, spriteX=0, spriteY=0, spriteAncho=32, spriteAlto=32, g;
    QPixmap hojaSprites, spriteActual;
    QTimer *timerMovimiento;
    bool dirX = true, dirY = true;
    Goku* goku;

private slots:
    void movimientoParabolico();
};

#endif // OBSTACULO_H
