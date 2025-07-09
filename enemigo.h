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
    std::list<Obstaculo*>& proyectiles;
    QTimer* timerObstaculo = nullptr;
    Goku* goku = nullptr;
    std::function<void(Obstaculo*)> eliminarObstaculo;

private slots:
    void movimiento();
    void disparar();

public:
    Enemigo(unsigned int x, unsigned int y, std::list<Obstaculo*>& proyectiles, Goku* goku, std::function<void(Obstaculo*)> eliminarObstaculo, unsigned char nivel);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
    ~Enemigo();
};

#endif // ENEMIGO_H
