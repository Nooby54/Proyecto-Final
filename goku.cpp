#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include "goku.h"
#include "qgraphicsscene.h"

#define g 0.5

Goku::Goku(unsigned int x, unsigned int y, QGraphicsView *vista, vector<Enemigo*>& enemigos):Personaje(x,y,64,64,15,70),vista(vista),enemigos(enemigos){
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

    // Kamehameha
    kamehameha = new Kamehameha(enemigos);
    vista->scene()->addItem(kamehameha);
    kamehameha->setPos(0, 0);
    kamehameha->setVisible(false);
    connect(kamehameha, &Kamehameha::terminado, this, &Goku::reanudarMovimiento);

    // Timers
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Goku::saltoParabolico);
    timerMovimiento->start(24);

    timerKamehameha = new QTimer(this);
    connect(timerKamehameha, &QTimer::timeout, this, &Goku::spriteKamehameha);
    timerKamehameha->start(60);
}

void Goku::keyPressEvent(QKeyEvent *event)
{
    if(kamehamehaActivo)
        return;
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
    case Qt::Key_Q:
        if (direccion) {
            contadorSprite = 0;
            kamehamehaActivo = true;
            saltoPausado = true;
        }
    }
}

void Goku::movimiento(int dx, int dy){
    if(x < 0){
        x = 920-spriteAncho;
    }
    else if(x+spriteAncho > 920){
        x = 0;
    }
    else{
        x+=dx;
    }

    y+=dy;
    setPos(x,y);
}

void Goku::configurarSprite(unsigned char dir){
    if(((dir == 5 || dir == 6) && (contadorSprite > 5)) || ((dir == 2 || dir == 1) && (contadorSprite > 2 || salto))){
        contadorSprite = 0;
    }
    spriteY = dir * spriteAlto;
    spriteX = spriteAncho * contadorSprite;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(192, 192, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    contadorSprite++;
}

void Goku::saltoParabolico()
{
    if (salto && !saltoPausado) {
        x += velX;
        velY += g;
        y += velY;

        if (velY > 0 && y >= dy) {
            y = dy;
            salto = false;
            velY = 0;
            velX = 0;
        }

        direccion ? configurarSprite(2) : configurarSprite(1);
        setPos(x, y);
    }
}

void Goku::spriteKamehameha(){
    if(kamehamehaActivo){
        spriteY = 3 * spriteAlto;
        spriteX = spriteAncho * contadorSprite;
        spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
        spriteActual = spriteActual.scaled(192, 192, Qt::KeepAspectRatio);
        setPixmap(spriteActual);
        if(contadorSprite < 5){
            contadorSprite++;
        }
        else if(contadorSprite == 5){
            contadorSprite++;
            kamehameha->setVisible(true);
            kamehameha->lanzar(x+180,y+110);
        }
    }
}

void Goku::reanudarMovimiento() {
    saltoPausado = false;
    kamehamehaActivo = false;
}
