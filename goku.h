#ifndef GOKU_H
#define GOKU_H

#include "kamehameha.h"
#include "personaje.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

class Goku : public Personaje
{
    Q_OBJECT

private:
    QTimer* timerKamehameha;
    Kamehameha* kamehameha;
    bool kamehamehaActivo = false, salto = false, saltoPausado = false;
    QGraphicsView *vista;
    vector<Enemigo*>& enemigos;

private slots:
    void saltoParabolico();
    void spriteKamehameha();
    void reanudarMovimiento();

public:
    Goku(unsigned int x, unsigned int y, QGraphicsView *vista, vector<Enemigo*>& enemigos);
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
};

#endif // GOKU_H
