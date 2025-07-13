#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "enemigo.h"
#include "esfera.h"
#include "obstaculo.h"
#include "plataforma.h"
#include "qgraphicsscene.h"
#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    unsigned short int id, contadorEsferas = 0, esferasRecolectadas = 0;
    Goku* goku = nullptr;
    std::vector<Enemigo*> enemigos;
    std::list<Obstaculo*> proyectiles;
    std::array<Plataforma*,8> plataformas;
    QGraphicsScene* escena;
    QTimer *timerEscena = nullptr, *timerFondo = nullptr, *timerObstaculos = nullptr;
    QPixmap fondo;
    int ultimaXPlataforma = 0;
    std::array<Esfera*, 7> esferas;
    QMediaPlayer* gestorSonido = nullptr;
    QAudioOutput* audioOutput = nullptr;
    QGraphicsPixmapItem *fondo1 = nullptr, *fondo2 = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void eliminarObstaculo(Obstaculo* p);
    void finalizarNivel();
    void gestionarSonido(QString url, int loop);
    void gestionarFondo(QString url);
    void gestionarLabelsNiveles(bool modo);

private slots:
    void on_nivel1_clicked();
    void on_nivel2_clicked();
    void actualizar();
    void gano();
    void perdio();
    void on_teclas_clicked();
    void on_salir_clicked();
    void on_menu_clicked();
};
#endif // MAINWINDOW_H
