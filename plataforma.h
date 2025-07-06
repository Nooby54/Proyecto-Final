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
    QTimer *timerMovimiento;

private slots:
    void mover();

public:
    Plataforma();
};


#endif // PLATAFORMA_H
