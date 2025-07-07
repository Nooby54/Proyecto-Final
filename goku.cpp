#include <QKeyEvent>
#include <QTimer>
#include "goku.h"
#include "qgraphicsscene.h"

#define g 0.5

Goku::Goku(qreal x, qreal y, QGraphicsView *vista, vector<Enemigo*>& enemigos, std::array<Plataforma*,8>& plataformas, unsigned char nivel):Personaje(x,y,64,64,15,70,nivel),vista(vista),enemigos(enemigos),plataformas(plataformas){
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

    timerKamehameha = new QTimer(this);
    connect(timerKamehameha, &QTimer::timeout, this, &Goku::spriteKamehameha);
    timerKamehameha->start(60);

    timerCooldown = new QTimer(this);
    timerCooldown->setSingleShot(true);
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
        movimiento(10,0);
        direccion = true;
        configurarSprite(5);
        if(nivel == 1){
            emit moverFondo();
        }
        break;
    case Qt::Key_Space:
        //direccion [Izquierda (False), Derecha (True)]
        if(salto && (nivel == 1)){
            return;
        }
        salto = true;
        velX = velInicial * cos(qDegreesToRadians(theta));
        velY = -velInicial * sin(qDegreesToRadians(theta));
        if (!direccion){
            velX *= -1;
        }
        break;
    case Qt::Key_Q:
        if (direccion && !(timerCooldown->isActive()) && (nivel == 2)) {
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
    else if((x + spriteAncho > 950) && (nivel == 1)){
        x = 950 - spriteAncho;
    }
    else if((x+spriteAncho > 1000) && (nivel == 2)){
        x = 1000 - spriteAncho;
    }
    else{
        x+=dx;
    }
    y+=dy;

    if (!salto && y < 450 - spriteAlto) {
        salto = true;
        velX = 0;
        velY = 0;
    }

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
        x += velX;
        velY += g;
        if(y < 0){
            y = 0;
            velY = 0;
        }
        else{
            y += velY;
        }

        if (velY > 0 && y >= dy) {
            y = dy;
            salto = false;
            velY = 0;
            velX = 0;
        }

        if((x+ spriteAncho > 950) && (nivel == 1)){
            x = 950 - spriteAncho;
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

        if(nivel == 1){
            for (auto plataforma : plataformas) {
                if (this->collidesWithItem(plataforma)) {
                    QRectF gokuRect = this->sceneBoundingRect();
                    QRectF plataformaRect = plataforma->sceneBoundingRect();
                    if (velY > 0 && gokuRect.bottom() >= plataformaRect.top()) {
                        y =  plataformaRect.top() - 190;
                        velY = 0;
                        velX = 0;
                        salto = false;
                        break;
                    }
                }
            }
        }
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
    timerCooldown->start(1500);
}

void Goku::recibirDanio(){
    configurarSprite(6);
    vida-=15;
    if(vida <= 0){
        timerMovimiento->stop();
        timerCooldown->stop();
        timerKamehameha->stop();
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
