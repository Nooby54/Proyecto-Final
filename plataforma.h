#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Plataforma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    qreal x, y;
    QPixmap sprite;
    bool tieneEsfera = false, reposicionado = false;

public:
    Plataforma(qreal x, qreal y);
    qreal getX();
    void setX(qreal x);
    qreal getY();
    void setY(qreal y);
    void mover();
    bool getTieneEsfera();
    void setTieneEsfera(bool tieneEsfera);
    bool getReposicionado();
    void setReposicionado(bool reposicionado);
};


#endif // PLATAFORMA_H
