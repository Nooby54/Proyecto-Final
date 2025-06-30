#ifndef KAMEHAMEHA_H
#define KAMEHAMEHA_H

#include "enemigo.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>

class Kamehameha: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    qreal x, y, velX, velY;
    unsigned int dx, dy, contadorSprite=0, spriteX, spriteY, spriteAncho=128, spriteAlto=64;
    float escalaX = 1.0;
    QPixmap hojaSprites, spriteActual;
    QTimer* timerMovimiento;
    QTimer* timerSprite;
private slots:
    void actualizarMovimiento();
signals:
    void terminado();
public:
    Kamehameha();
    void lanzar(unsigned int x, unsigned int y);
    void hacerDanio(Enemigo* enemigo);
};

#endif // KAMEHAMEHA_H
