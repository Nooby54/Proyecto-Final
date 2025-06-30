#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigo: public Personaje
{
    Q_OBJECT
private:
    unsigned short int tiempoSprite = 0;
private slots:
    void movimiento();
public:
    Enemigo(unsigned int x, unsigned int y);
    void configurarSprite(int dir) override;
    void lanzarProyectil();
};

#endif // ENEMIGO_H
