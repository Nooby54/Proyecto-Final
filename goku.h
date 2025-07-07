#ifndef GOKU_H
#define GOKU_H

#include "kamehameha.h"
#include "personaje.h"
#include "plataforma.h"
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

class Goku : public Personaje
{
    Q_OBJECT

private:
    QTimer *timerKamehameha, *timerCooldown;
    Kamehameha* kamehameha = nullptr;
    bool kamehamehaActivo = false, salto = false, saltoPausado = false;
    QGraphicsView *vista;
    vector<Enemigo*>& enemigos;
    std::array<Plataforma*,8>& plataformas;
    unsigned int dx = 0, dy = 0;

private slots:
    void saltoParabolico();
    void spriteKamehameha();
    void reanudarMovimiento();

signals:
    void derrotado();
    void moverFondo();

public:
    Goku(qreal x, qreal y, QGraphicsView *vista, vector<Enemigo*>& enemigos, std::array<Plataforma*,8>& plataformas, unsigned char nivel);
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
    bool getkamehamehaActivo() const;
    Kamehameha* getKamehameha() const;
};

#endif // GOKU_H
