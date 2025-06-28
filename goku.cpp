#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "goku.h"

#define g 1.2

Goku::Goku():Personaje(200,200,64,64,25,75){
    spriteX = 0*spriteAncho;
    spriteY = 4*spriteAlto;
    velInicial = 10;

    hojaSprites.load(":/sprites/Goku (64x64).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
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
        movimiento(-5,0);
        direccionSalto = false;
        configurarSprite(5);
        break;
    case Qt::Key_D:
        movimiento(5,0);
        direccionSalto = true;
        configurarSprite(6);
        break;
    case Qt::Key_Space:
        if (!salto) {
            salto = true;

            qreal anguloRad = qDegreesToRadians(theta);

            velX = velInicial * cos(anguloRad);
            velY = -velInicial * sin(anguloRad);
            if (!direccionSalto)
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
        if (contador == 5)
            contador = 0;
    }
    else if(dir == 2){
        if(contador > 2){
            contador = 0;
        }
    }
    spriteY = dir * spriteAlto;
    spriteX = spriteAncho * contador;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);
    contador++;
}

void Goku::actualizarMovimiento()
{
    if (salto) {
        x += velX;
        velY += g;
        y += velY;

        if (velY > 0 && y >= 200) {
            y = 200;
            salto = false;
            velY = 0;
            velX = 0;
        }
        configurarSprite(2);
        setPos(x, y);
    }
}
