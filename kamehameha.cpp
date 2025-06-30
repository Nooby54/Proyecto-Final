#include "kamehameha.h"

#include <QTimer>

Kamehameha::Kamehameha() {
    hojaSprites.load(":/sprites/Kamehameha (128x64).png");
    spriteX = 0;
    spriteY = 0;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    setTransformOriginPoint(0, spriteAlto / 2); // escalar desde el borde izquierdo
}

void Kamehameha::lanzar(unsigned int dx, unsigned int dy){
    x = dx;
    y = dy;
    setPos(x, y);
    setTransform(QTransform::fromScale(escalaX, 1));

    if (!timerMovimiento) {
        timerMovimiento = new QTimer(this);
        connect(timerMovimiento, &QTimer::timeout, this, &Kamehameha::actualizarMovimiento);
    }

    timerMovimiento->start(15);
}

void Kamehameha::actualizarMovimiento()
{
    escalaX += 0.5;
    setTransform(QTransform::fromScale(escalaX, 1));
    if(escalaX > 10.0) escalaX = 10.0;
    if (x + spriteAncho * escalaX > 1400) {
        timerMovimiento->stop();
        QTimer::singleShot(800, this, [this]() {
            escalaX = 1.0;
            setTransform(QTransform::fromScale(1.0, 1));
            setVisible(false);
        });
        // Verificar las colisiones
    }
}
