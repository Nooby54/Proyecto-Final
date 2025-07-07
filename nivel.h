#ifndef NIVEL_H
#define NIVEL_H

#include "esfera.h"
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
    unsigned short int id, contadorEsferas = 0;
    Goku* goku = nullptr;
    std::vector<Enemigo*> enemigos;
    std::list<Proyectil*> proyectiles;
    std::array<Plataforma*,8> plataformas;
    QGraphicsScene* escena;
    QTimer *timerEscena;
    QPixmap fondo;
    int ultimaXPlataforma = 0;
    std::array<Esfera*, 7> esferas;
    QTimer* timerColisionesEsferas;

private slots:
    void finalizarNivel();
    void actualizar();
    void verificarColisionesEsferas();

public:
    Nivel(int id);
    void iniciarNivel(Ui::MainWindow *ui);
    void eliminarProyectil(Proyectil* p);
};

#endif // NIVEL_H
