#include "kamehameha.h"
#include "enemigo.h"
#include <QTimer>
#include <QSoundEffect>

Kamehameha::Kamehameha(vector<Enemigo*>& enemigos):enemigos(enemigos) {
    hojaSprites.load(":/sprites/Kamehameha (192x64).png");
    spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteActual);
    setTransformOriginPoint(0, spriteAlto / 2);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Kamehameha::mover);

    timerSprite = new QTimer(this);
    connect(timerSprite, &QTimer::timeout, this, [this]() {
        if(contadorSprite == 5){
            contadorSprite = 0;
        }
        spriteX = spriteAncho * contadorSprite;
        spriteActual = hojaSprites.copy(spriteX, spriteY, spriteAncho, spriteAlto);
        setPixmap(spriteActual);
        setTransform(QTransform::fromScale(escalaX, 1));
        contadorSprite++;
    });

    efectoKamehameha = new QSoundEffect(this);
    efectoKamehameha->setSource(QUrl::fromLocalFile(":/audios/Kamehameha.wav"));
    efectoKamehameha->play();
}

void Kamehameha::lanzar(unsigned int dx, unsigned int dy){
    x = dx;
    y = dy;
    setPos(x, y);
    setTransform(QTransform::fromScale(escalaX, 1));
    timerMovimiento->start(15);
}

void Kamehameha::mover()
{
    escalaX += 0.5;
    setTransform(QTransform::fromScale(escalaX, 1));
    if (x + spriteAncho * escalaX > 1400) {
        timerMovimiento->stop();
        timerSprite->start(100);

        QTimer::singleShot(800, this, [this]() {
            if (timerSprite) timerSprite->stop();
            emit terminado();
        });
    }

    for (Enemigo* enemigo : enemigos) {
        if (enemigo && this->collidesWithItem(enemigo)) {
            enemigo->Enemigo::recibirDanio();
        }
    }
}

Kamehameha::~Kamehameha(){}
