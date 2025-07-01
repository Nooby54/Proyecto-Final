#include "personaje.h"

Personaje::Personaje(){}

Personaje::Personaje(unsigned int x, unsigned int y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta):
    x(x),y(y),spriteAncho(spriteAncho),spriteAlto(spriteAlto),velInicial(velInicial),theta(theta){}

void Personaje::recibirDanio(){
    vida-=10;
    qDebug() << vida;
}

void Personaje::configurarSprite(unsigned char dir){}
Personaje::~Personaje(){}
