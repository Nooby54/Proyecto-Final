#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigo: public Personaje
{
    Q_OBJECT

private:
    unsigned char tiempoSprite = 0;
    bool danio = false;

private slots:
    void movimiento();
    void lanzarProyectil();

public:
    Enemigo(unsigned int x, unsigned int y);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
};

#endif // ENEMIGO_H
