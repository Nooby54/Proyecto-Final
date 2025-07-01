#include "kamehameha.h"
#include "enemigo.h"

#include <QTimer>

Kamehameha::Kamehameha(vector<Enemigo*>& enemigos):enemigos(enemigos) {
    hojaSprites.load(":/sprites/Kamehameha (192x64).png");
    spriteX = 0;
    spriteY = 0;
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);

    setTransformOriginPoint(0, spriteAlto / 2);
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
    if (x + spriteAncho * escalaX > 1400) {
        timerMovimiento->stop();
        if (!timerSprite) {
            timerSprite = new QTimer(this);
            connect(timerSprite, &QTimer::timeout, this, [this]() {
                if(contadorSprite == 5){
                    contadorSprite = 0;
                }
                spriteY = 0 * spriteAlto;
                spriteX = spriteAncho * contadorSprite;
                spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
                setPixmap(spriteActual);
                setTransform(QTransform::fromScale(escalaX, 1));
                contadorSprite++;
            });
        }
        timerSprite->start(100);

        QTimer::singleShot(800, this, [this]() {
            contadorSprite = 0;
            escalaX = 1.0;
            setTransform(QTransform::fromScale(1.0, 1));
            setVisible(false);
            if (timerSprite) timerSprite->stop();
            emit terminado();

        });
    }
    for (Enemigo* enemigo : enemigos) {
        if (this->collidesWithItem(enemigo)) {
            enemigo->Enemigo::recibirDanio();
        }
    }
}
