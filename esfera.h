#ifndef ESFERA_H
#define ESFERA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Esfera : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

private:
    unsigned char id;
    bool recolectada;
    QTimer* timerMovimiento;
    qreal yOriginal, x, y;
    float fase;
    QPixmap hojaSprites, spriteActual;

public:
    Esfera(unsigned char id, qreal x, qreal y);
    bool estaRecolectada() const;
    void recolectar();
    void mover();

private slots:
    void moverSenoidal();
};

#endif // ESFERA_H
