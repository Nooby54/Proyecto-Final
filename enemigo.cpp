#include "enemigo.h"
#include <QTimer>

//unsigned int x, unsigned int y, unsigned int spriteAncho, unsigned int spriteAlto, qreal velInicial, qreal theta
Enemigo::Enemigo(unsigned int x, unsigned int y):Personaje(x,y,41,94,0,0) {
    hojaSprites.load(":/sprites/Piccolo (41x94).png");
    spriteX = 0*spriteAncho;
    spriteY = 0*spriteAlto;

    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(123, 282, Qt::KeepAspectRatio);
    setPixmap(spriteActual);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, [=]()
            {
                movimiento();
                configurarSprite(1);
                tiempoSprite++;
            });
    timerMovimiento->start(45);
}

void Enemigo::movimiento(){
    //direccion [Baja (False), Sube (True)]
    !direccion ? y+=10 : y-=10;

    if(y>448){
        direccion = true;
    }
    else if(y<1){
        direccion = false;
    }
    setPos(x, y);
}

void Enemigo::configurarSprite(unsigned char dir){
    if(tiempoSprite%5 == 0){
        contadorSprite = (contadorSprite == 1) ? 0 : 1;
        tiempoSprite = 0;
    }
    spriteY = dir * spriteAlto;
    spriteX = spriteAncho * contadorSprite;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(123, 282, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
}

void Enemigo::recibirDanio(){
    vida-=10;
    configurarSprite(0);
}
void Enemigo::lanzarProyectil(){}
