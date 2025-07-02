#include "obstaculo.h"

Obstaculo::Obstaculo() {
    hojaSprites.load(":/sprites/proyectil (32x32).png");
    spriteX = 0;
    spriteY = 0;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);
}

void Obstaculo::mover(qreal velInicial){
    // MRUA

}
void Obstaculo::mover(qreal angulo, qreal velInicial){
    // Parabolico
}
void hacerDanio(Goku* goku);
