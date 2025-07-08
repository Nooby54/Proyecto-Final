#include "personaje.h"

Personaje::Personaje(){}

Personaje::Personaje(qreal x, qreal y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta, unsigned char nivel):
    x(x),y(y),velInicial(velInicial),theta(theta),spriteAncho(spriteAncho),spriteAlto(spriteAlto),nivel(nivel){}

qreal Personaje::getVelY(){
    return velY;
}

void Personaje::setVelY(qreal velY){
    this->velY = velY;
}

void Personaje::setY(qreal y){
    this->y = y;
}

void Personaje::setVelX(qreal velX){
    this->velX = velX;
}

qreal Personaje::getY(){
    return y;
}

void Personaje::recibirDanio(){}

void Personaje::configurarSprite(unsigned char dir){}

Personaje::~Personaje(){}
