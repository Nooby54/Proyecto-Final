#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "obstaculo.h"
#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemigo: public Personaje
{
    Q_OBJECT

private:
    unsigned char tiempoSprite = 0;
    bool danio = false;
    std::list<Obstaculo*>& proyectiles;
    QTimer* timerProyectil;
    Goku* goku;

private slots:
    void movimiento();
    void disparar();

public:
    Enemigo(unsigned int x, unsigned int y, std::list<Obstaculo*>& proyectiles, Goku* goku);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
};

#endif // ENEMIGO_H
