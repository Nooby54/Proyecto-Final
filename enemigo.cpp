#include "enemigo.h"
#include <QTimer>
#include <QRandomGenerator>


Enemigo::Enemigo(unsigned int x, unsigned int y, std::list<Obstaculo *> &proyectiles, Goku* goku):Personaje(x,y,41,94,0,0), proyectiles(proyectiles),goku(goku) {
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

    timerProyectil = new QTimer(this);
    connect(timerProyectil, &QTimer::timeout, this, &Enemigo::disparar);
    timerProyectil->start(300);
}

void Enemigo::movimiento(){
    //direccion [Baja (False), Sube (True)]
    !direccion ? y+=10 : y-=10;

    if(y>448){
        direccion = true;
    }
    else if(y<100){
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
    vida-=5;
    configurarSprite(0);
    emit actualizarVida(vida);
}

void Enemigo::disparar(){
    int velAleatoria = QRandomGenerator::global()->bounded(100, 401);
    int anguloAleatorio = QRandomGenerator::global()->bounded(120, 221);
    int gravedadAleatoria = QRandomGenerator::global()->bounded(30, 51);
    bool modo = QRandomGenerator::global()->bounded(0,2);

    Obstaculo* nuevo = new Obstaculo(goku, velAleatoria, x, y + (spriteAlto/2), anguloAleatorio, gravedadAleatoria,modo);
    proyectiles.push_back(nuevo);
    this->scene()->addItem(nuevo);
    nuevo->setPos(x, y + (spriteAlto/2));
    nuevo->mover();
}
