#ifndef ESFERA_H
#define ESFERA_H

#include "goku.h"
#include "plataforma.h"
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Esfera : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    unsigned char id;
    bool recolectada = false;
    QTimer* timerMovimiento = nullptr;
    qreal yOriginal, x, y;
    float fase = 0;
    QPixmap hojaSprites, spriteActual;
    Goku* goku = nullptr;
    Plataforma* plataforma = nullptr;
    QSoundEffect* efecto = nullptr;

signals:
    void esferaRecolectada();

private slots:
    void moverSenoidal();

public:
    Esfera(unsigned char id, qreal x, qreal y, Goku* goku, Plataforma* plataforma);
    bool getRecolectada();
    void mover();
    ~Esfera();
};

#endif // ESFERA_H
