#ifndef GOKU_H
#define GOKU_H

#include "personaje.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Goku : public Personaje
{
    Q_OBJECT
private:
    bool kamehameha;
public:
    Goku();
    void lanzarKamehameha();
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
};

#endif // GOKU_H
