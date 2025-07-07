#ifndef PROYECTIL_H
#define PROYECTIL_H

class Goku;

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Proyectil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y, vX, vY, angulo, velInicial, theta, xIn, yIn, tiempo=0;
    unsigned int dx, dy, contadorSprite, spriteX=0, spriteY=0, spriteAncho=32, spriteAlto=32, g;
    QPixmap hojaSprites, spriteActual;
    QTimer *timerMovimiento;
    bool dirX = true, dirY = true, modo = true;
    Goku* goku;
    std::function<void(Proyectil*)> eliminarProyectil;

private slots:
    void movimiento();

public:
    Proyectil(std::function<void(Proyectil*)> eliminarProyectil, Goku* goku, float velIn, qreal xIn, qreal yIn, float theta, unsigned int g, bool modo);
    void mover();
    ~Proyectil();
};

#endif // PROYECTIL_H
