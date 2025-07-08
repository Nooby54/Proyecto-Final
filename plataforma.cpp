#include "plataforma.h"
#include "qbrush.h"
#include <QRandomGenerator>

Plataforma::Plataforma(qreal x, qreal y):x(x), y(y) {
    sprite.load(":/sprites/Plataforma (48x16).png");
    sprite = sprite.scaled(150, 50, Qt::IgnoreAspectRatio);
    setPixmap(sprite);
    setPos(x, y);
}

void Plataforma::mover(){
    x-=5;
    setPos(x,y);
}

qreal Plataforma::getX(){
    return x;
}

void Plataforma::setX(qreal x){
    this->x = x;
}

qreal Plataforma::getY(){
    return y;
}

void Plataforma::setY(qreal y){
    this->y = y;
}

bool Plataforma::getTieneEsfera(){
    return tieneEsfera;
}

void Plataforma::setTieneEsfera(bool tieneEsfera){
    this->tieneEsfera = tieneEsfera;
}

bool Plataforma::getReposicionado(){
    return reposicionado;
}

void Plataforma::setReposicionado(bool reposicionado){
    this->reposicionado = reposicionado;
}
