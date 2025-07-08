#include "obstaculo.h"
#include "goku.h"
#include <QTimer>

Obstaculo::Obstaculo(std::function<void(Obstaculo*)> eliminarObstaculo, Goku* goku, float velInicial, qreal xIn, qreal yIn, float theta, unsigned int g, bool modo)
    : x(xIn), y(yIn), velInicial(velInicial), xIn(xIn), yIn(yIn),g(g),modo(modo),goku(goku), eliminarObstaculo(eliminarObstaculo) {
    hojaSprites.load(":/sprites/proyectil (32x32).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, [=]() { movimiento(); });
    this->theta = qDegreesToRadians(theta);
}

void Obstaculo::mover(){
    timerMovimiento->start(50);
}

void Obstaculo::movimiento()
{
    if(modo){
        vX = velInicial * cos(theta);
        x = xIn + (vX*tiempo);
        y = yIn + (-velInicial * sin(theta) * tiempo) + (0.5 * g * tiempo * tiempo);
        vY = -velInicial * sin(theta) + g * tiempo;

        if(y<0){
            velInicial = sqrt(vX * vX + vY * vY)*0.8;
            theta = atan2(vY,vX);
            velInicial *= 0.8;
            tiempo = 0;
            dirY = y < 0 ? 1 : 0;
            yIn = y - (dirY ? -10 : 10);
            xIn = x;
        }
    }else{
        x = xIn - velInicial*tiempo;
    }
    setPos(x, y);
    tiempo += 0.1;
    if (collidesWithItem(goku) || (collidesWithItem(goku->getKamehameha()) && goku->getkamehamehaActivo())) {
        if(!goku->getkamehamehaActivo()){
            goku->recibirDanio();
        }
        timerMovimiento->stop();
        eliminarObstaculo(this);
        return;
    }

    if(x>1400 || x+spriteAncho<0 || y>730){
        timerMovimiento->stop();
        eliminarObstaculo(this);
        return;
    }
}

Obstaculo::~Obstaculo(){}
