#ifndef NIVEL_H
#define NIVEL_H

#include "goku.h"
#include "enemigo.h"
#include "proyectil.h"
#include "ui_mainwindow.h"

#include <vector>
#include <list>
#include <QGraphicsScene>

class Nivel: public QObject {
    Q_OBJECT

private:
    unsigned short int id;
    Goku* goku = nullptr;
    std::vector<Enemigo*> enemigos;
    std::list<Proyectil*> proyectiles;
    QGraphicsScene* escena;
    QTimer *timerEscena;
    QPixmap fondo;

private slots:
    void finalizarNivel();

public:
    Nivel(int id);
    void iniciarNivel(Ui::MainWindow *ui);
};

#endif // NIVEL_H
