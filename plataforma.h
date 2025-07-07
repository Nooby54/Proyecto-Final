#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QTimer>

class Plataforma : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    qreal x, y;

public:
    Plataforma(qreal x, qreal y);
    qreal getX();
    void setX(qreal x);
    qreal getY();
    void setY(qreal y);
    void mover();
};


#endif // PLATAFORMA_H
