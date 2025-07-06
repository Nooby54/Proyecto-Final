#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "proyectil.h"
#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigo: public Personaje
{
    Q_OBJECT

private:
    unsigned char tiempoSprite = 0;
    std::list<Proyectil*>& proyectiles;
    QTimer* timerProyectil;
    Goku* goku;

private slots:
    void movimiento();
    void disparar();

public:
    Enemigo(unsigned int x, unsigned int y, std::list<Proyectil*>& proyectiles, Goku* goku);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
};

#endif // ENEMIGO_H
