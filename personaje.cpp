#include "personaje.h"

Personaje::Personaje(){}

Personaje::Personaje(qreal x, qreal y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta, unsigned char nivel):
    x(x),y(y),velInicial(velInicial),theta(theta),spriteAncho(spriteAncho),spriteAlto(spriteAlto),nivel(nivel){}

void Personaje::recibirDanio(){}

void Personaje::configurarSprite(unsigned char dir){}

Personaje::~Personaje(){}
