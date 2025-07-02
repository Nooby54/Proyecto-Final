#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Obstaculo(float velIn,qreal xIn, qreal yIn, float theta, unsigned int g);
    void movParabolico(float* dt);
    void iniMov();

private:
    qreal x, y, vX, vY, angulo, velInicial, velIn, theta, xIn, yIn, tiempo=0;
    unsigned int dx, dy, contadorSprite, spriteX=0, spriteY=0, spriteAncho=32, spriteAlto=32, g;
    QPixmap hojaSprites, spriteActual;
    QTimer *timerMovimiento;
    bool dirX = true, dirY = true;

private slots:
    void movParabolico();
};

#endif // OBSTACULO_H
