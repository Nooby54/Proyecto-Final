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
    bool salto = false;
private slots:
    void actualizarMovimiento();
public:
    Goku(unsigned int x, unsigned int y);
    void lanzarKamehameha();
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(int dir) override;
    void movParabolico();
};

#endif // GOKU_H
