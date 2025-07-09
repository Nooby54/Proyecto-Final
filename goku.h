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
    QTimer *timerKamehameha = nullptr, *timerCooldown = nullptr;
    Kamehameha* kamehameha = nullptr;
    bool kamehamehaActivo = false, salto = false, saltoPausado = false, debeCaer = false;
    QGraphicsView *vista = nullptr;
    vector<Enemigo*>& enemigos;
    unsigned int dx = 0, dy = 0;

private slots:
    void saltoParabolico();
    void spriteKamehameha();
    void reanudarMovimiento();

public:
    Goku(qreal x, qreal y, QGraphicsView *vista, vector<Enemigo*>& enemigos, unsigned char nivel);
    void keyPressEvent(QKeyEvent *event) override;
    void movimiento(int dx, int dy);
    void configurarSprite(unsigned char dir) override;
    void recibirDanio() override;
    bool getkamehamehaActivo() const;
    void setSalto(bool salto);
    bool getSalto();
    bool getDebeCaer();
    void setDebeCaer(bool debeCaer);
    Kamehameha* getKamehameha() const;
    ~Goku();
};

#endif // GOKU_H
