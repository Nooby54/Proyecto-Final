#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigo: public Personaje
{
    Q_OBJECT
public:
    Enemigo();
    void mover();
    void lanzarProyectil();
};

#endif // ENEMIGO_H
