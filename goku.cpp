#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "goku.h"

#define g 0.5

Goku::Goku(unsigned int x, unsigned int y):Personaje(x,y,64,64,15,70){
    spriteX = 0*spriteAncho;
    spriteY = 4*spriteAlto;
    dy = y;
    dx = x;

    hojaSprites.load(":/sprites/Goku (64x64).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(192, 192, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Goku::actualizarMovimiento);
    timerMovimiento->start(24);
}

void Goku::lanzarKamehameha(){}

void Goku::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        if(!salto){
            direccion = false;
            movimiento(-10,0);
            configurarSprite(5);
        }
        break;
    case Qt::Key_D:
        if(!salto){
            movimiento(10,0);
            direccion = true;
            configurarSprite(6);
        }
        break;
    case Qt::Key_Space:
        //direccion [Izquierda (False), Derecha (True)]
        if (!salto) {
            salto = true;
            qreal anguloRad = qDegreesToRadians(theta);
            velX = velInicial * cos(anguloRad);
            velY = -velInicial * sin(anguloRad);
            if (!direccion)
                velX *= -1;
        }
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Goku::movimiento(int dx, int dy){
    x+=dx;
    y+=dy;
    setPos(x,y);
}

void Goku::configurarSprite(int dir){
    if(dir == 5 || dir == 6){
        if (contador == 6)
            contador = 0;
    }
    else if(dir == 2 || dir == 1){
        if(contador > 2 || salto){
            contador = 0;
        }
    }
    spriteY = dir * spriteAlto;
    spriteX = spriteAncho * contador;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(192, 192, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    contador++;
}

void Goku::actualizarMovimiento()
{
    if (salto) {
        x += velX;
        velY += g;
        y += velY;

        if (velY > 0 && y >= dy) {
            y = dy;
            salto = false;
            velY = 0;
            velX = 0;
        }

        if(direccion){
            configurarSprite(2);
        }
        else{
            configurarSprite(1);
        }
        setPos(x, y);
    }
}
