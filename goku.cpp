#include <QKeyEvent>
#include <QTimer>
#include "goku.h"
#include "qgraphicsscene.h"

#define g 0.5

Goku::Goku(qreal x, qreal y, QGraphicsView *vista, vector<Enemigo*>& enemigos, unsigned char nivel):Personaje(x,y,64,64,15,70,nivel),vista(vista),enemigos(enemigos){
    spriteX = 0*spriteAncho;
    spriteY = 3*spriteAlto;
    dy = y;
    dx = x;

    hojaSprites.load(":/sprites/Goku (64x64).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    spriteActual = spriteActual.scaled(192, 192, Qt::KeepAspectRatio);
    setPixmap(spriteActual);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setPos(x,y);

    // Timers
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Goku::saltoParabolico);
    timerMovimiento->start(24);

    if(nivel == 2){
        timerKamehameha = new QTimer(this);
        connect(timerKamehameha, &QTimer::timeout, this, &Goku::spriteKamehameha);
        timerKamehameha->start(60);

        timerCooldown = new QTimer(this);
        timerCooldown->setSingleShot(true);
    }
}

void Goku::keyPressEvent(QKeyEvent *event)
{
    if(kamehamehaActivo)
        return;
    switch (event->key()) {
    case Qt::Key_A:
        direccion = false;
        movimiento(-10,0);
        configurarSprite(4);
        break;
    case Qt::Key_D:
        direccion = true;
        movimiento(10,0);
        configurarSprite(5);
        if(nivel == 1){
        }
        break;
    case Qt::Key_Space:
        //direccion [Izquierda (False), Derecha (True)]
        if(salto && (nivel == 1)){
            return;
        }
        salto = true;
        velY = -velInicial * sin(qDegreesToRadians(theta));
        if(nivel == 2){
            velX = velInicial * cos(qDegreesToRadians(theta));
            if (!direccion){
                velX *= -1;
            }
        }
        break;
    case Qt::Key_Q:
        if(nivel != 2) return;
        if (direccion && !(timerCooldown->isActive())) {
            kamehameha = new Kamehameha(enemigos);
            vista->scene()->addItem(kamehameha);
            kamehameha->setPos(0, 0);
            kamehameha->setVisible(false);
            connect(kamehameha, &Kamehameha::terminado, this, &Goku::reanudarMovimiento);
            contadorSprite = 0;
            kamehamehaActivo = true;
            saltoPausado = true;
        }
        break;
    }
}

void Goku::movimiento(int dx, int dy){
    if(x < 0){
        x = 1;
    }
    else if((x + spriteAncho > 700) && (nivel == 1)) x = 700 - spriteAncho;
    else if((x + spriteAncho > 1000) && (nivel == 2)) x = 1000 - spriteAncho;
    else x+=dx;
    y+=dy;
    setPos(x,y);
}

void Goku::configurarSprite(unsigned char dir){
    if(((dir == 4 || dir == 5) && (contadorSprite > 5)) || ((dir == 0 || dir == 1) && (contadorSprite > 1 || salto)) || (dir == 6 && contadorSprite > 0)){
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
        velY += g;
        if(nivel == 2){
            x += velX;
            if(y < 0){
                y = 0;
                velY = 0;
            }
            else{
                y += velY;
            }
        }else{
            y+= velY;
        }

        if (velY > 0 && y >= dy) {
            y = dy;
            salto = false;
            debeCaer = false;
            velY = 0;
            velX = 0;
        }

        else if((x + spriteAncho > 1000) && (nivel == 2)){
            direccion = false;
            x = 1000 - spriteAncho;
            velX*=-1;
        }

        else if(x < 0){
            direccion = true;
            x = 0;
            velX*=-1;
        }

        direccion ? configurarSprite(1) : configurarSprite(0);
        setPos(x, y);
    }else if(debeCaer){
        velY+=g;
        y+=velY;

        if (velY > 0 && y >= dy) {
            y = dy;
            salto = false;
            debeCaer = false;
            velY = 0;
            velX = 0;
        }
        setPos(x,y);
    }
}

void Goku::spriteKamehameha(){
    if(kamehamehaActivo){
        spriteY = 2 * spriteAlto;
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
    delete kamehameha;
    kamehameha = nullptr;
    timerCooldown->start(1200);
}

void Goku::recibirDanio(){
    configurarSprite(6);
    vida-=15;
    if(vida <= 0){
        if(timerMovimiento) timerMovimiento->stop();
        if(timerCooldown) timerCooldown->stop();
        if(timerKamehameha) timerKamehameha->stop();
        emit derrotado();
        emit actualizarVida(0);
    }
    else{
        emit actualizarVida(vida);
    }
}

bool Goku::getkamehamehaActivo() const{
    return kamehamehaActivo;
}

Kamehameha* Goku::getKamehameha() const{
    return kamehameha;
}

void Goku::setSalto(bool salto){
    this->salto = salto;
}

bool Goku::getSalto(){
    return salto;
}

bool Goku::getDebeCaer(){
    return debeCaer;
}

void Goku::setDebeCaer(bool debeCaer){
    this->debeCaer = debeCaer;
}
