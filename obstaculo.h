#ifndef OBSTACULO_H
#define OBSTACULO_H

class Goku;

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class Obstaculo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y, vX, vY, angulo, velInicial, theta, xIn, yIn, tiempo=0;
    unsigned int contadorSprite, spriteX=0, spriteY=0, spriteAncho=32, spriteAlto=32, g;
    unsigned char nivel;
    QPixmap sprite;
    QTimer *timerMovimiento = nullptr;
    bool dirX = true, dirY = true, modo = true;
    Goku* goku = nullptr;
    std::function<void(Obstaculo*)> eliminarObstaculo;

private slots:
    void movimiento();

public:
    Obstaculo(std::function<void(Obstaculo*)> eliminarObstaculo, Goku* goku, float velIn, qreal xIn, qreal yIn, float theta, unsigned int g, bool modo, unsigned char nivel);
    void mover();
    ~Obstaculo();
};

#endif // OBSTACULO_H
