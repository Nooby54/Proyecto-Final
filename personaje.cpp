#include "personaje.h"

Personaje::Personaje(){}

Personaje::Personaje(unsigned int x, unsigned int y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta):
    x(x),y(y),velInicial(velInicial),theta(theta),spriteAncho(spriteAncho),spriteAlto(spriteAlto){}

void Personaje::recibirDanio(){}

void Personaje::configurarSprite(unsigned char dir){}

Personaje::~Personaje(){}
