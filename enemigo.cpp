#include "enemigo.h"
#include <QTimer>
#include <QRandomGenerator>

Enemigo::Enemigo(unsigned int x, unsigned int y, std::list<Proyectil *> &proyectiles, Goku* goku, std::function<void(Proyectil*)> eliminarProyectil)
    : Personaje(x,y,41,94,0,0), proyectiles(proyectiles), goku(goku),eliminarProyectil(eliminarProyectil) {
    hojaSprites.load(":/sprites/Piccolo (41x94).png");
    spriteX = 0*spriteAncho;
    spriteY = 0*spriteAlto;

    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(123, 282, Qt::KeepAspectRatio);
    setPixmap(spriteActual);

    setPos(x,y);

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
    timerProyectil->start(500);
}

void Enemigo::movimiento(){
    //direccion [Baja (False), Sube (True)]
    !direccion ? y+=10 : y-=10;

    if(y>500){
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
    configurarSprite(0);
    if(vida < 1){
        timerMovimiento->stop();
        timerProyectil->stop();
        emit actualizarVida(0);
    }else{
        vida-=8;
        emit actualizarVida(vida);
    }
}

void Enemigo::disparar(){
    int velAleatoria = QRandomGenerator::global()->bounded(100, 401);
    int anguloAleatorio = QRandomGenerator::global()->bounded(120, 221);
    int gravedadAleatoria = QRandomGenerator::global()->bounded(30, 51);
    bool modo;
    if(y + (spriteAlto/2)>440){
        modo = 0;
    }
    else if(y<150){
        modo = 1;
    }
    else{
        modo = QRandomGenerator::global()->bounded(0,2);
    }

    Proyectil* nuevo = new Proyectil(eliminarProyectil, goku, velAleatoria, x, y + (spriteAlto/2), anguloAleatorio, gravedadAleatoria,modo);
    proyectiles.push_back(nuevo);
    this->scene()->addItem(nuevo);
    nuevo->setPos(x, y + (spriteAlto/2));
    nuevo->mover();
}
