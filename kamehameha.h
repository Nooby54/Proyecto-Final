#ifndef KAMEHAMEHA_H
#define KAMEHAMEHA_H

#include "enemigo.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>

using namespace std;

class Kamehameha: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y, velX, velY;
    unsigned int dx, dy, contadorSprite=0, spriteX=0, spriteY=0, spriteAncho=192, spriteAlto=64;
    float escalaX = 1.0;
    QPixmap hojaSprites, spriteActual;
    QTimer *timerMovimiento = nullptr, *timerSprite = nullptr;
    vector<Enemigo*>& enemigos;
    QSoundEffect* efectoKamehameha = nullptr;

private slots:
    void mover();

signals:
    void terminado();

public:
    Kamehameha(vector<Enemigo*>& enemigos);
    void lanzar(unsigned int x, unsigned int y);
    ~Kamehameha();
};

#endif // KAMEHAMEHA_H
