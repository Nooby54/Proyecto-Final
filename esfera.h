#ifndef ESFERA_H
#define ESFERA_H

#include "goku.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Esfera : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    unsigned char id;
    bool recolectada = false;
    QTimer* timerMovimiento;
    qreal yOriginal, x, y;
    float fase = 0;
    QPixmap hojaSprites, spriteActual;
    Goku* goku;
    Plataforma* plataforma;

signals:
    void esferaRecolectada();

public:
    Esfera(unsigned char id, qreal x, qreal y, Goku* goku, Plataforma* plataforma);
    bool getRecolectada();
    void mover();

private slots:
    void moverSenoidal();
};

#endif // ESFERA_H
