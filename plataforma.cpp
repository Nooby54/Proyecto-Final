#include "plataforma.h"
#include "qbrush.h"
#include <QRandomGenerator>

Plataforma::Plataforma(qreal x, qreal y):x(x), y(y) {
    setRect(0, 0, 150, 30);
    setBrush(QBrush(Qt::darkGreen));
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
