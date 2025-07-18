#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QAudioOutput>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(0, 0, 1400, 730);

    ui->graphicsView->scene()->setSceneRect(0, 0, 1400, 730);
    ui->graphicsView->setFixedSize(1400, 730);
    this->setFixedSize(1426, 756);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gestionarFondo(":/sprites/backgrounds/menu.png");

    // Diseño barras de vida
    ui->vidaEnemigo->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: purple;}");
    ui->iconoEnemigo->setPixmap(QPixmap(":/sprites/BarraDeVidaPiccolo (40x45).png"));
    ui->vidaEnemigo->setValue(255);

    ui->vidaGoku->setStyleSheet("QProgressBar{border: 2px solid black; background-color: rgba(255, 255, 255, 0); border-radius: 5px;} QProgressBar::chunk{background-color: orange;}");
    ui->iconoGoku->setPixmap(QPixmap(":/sprites/BarraDeVidaGoku (40x56).png"));
    ui->vidaGoku->setValue(255);

    ui->labelEsferas->setPixmap(QPixmap(":/sprites/Esferas (32x32).png").copy(0,0,32,32));

    ui->nivel1->setStyleSheet("QPushButton {background-color: #E4A74C; color: white; border: 2px solid #FCB851; border-radius: 10px; padding: 10px; font: bold 14px 'Segoe UI';} QPushButton:hover {background-color: #FFC977;} QPushButton:pressed {background-color: #FCB851;}");
    ui->nivel2->setStyleSheet("QPushButton {background-color: #E4A74C; color: white; border: 2px solid #FCB851; border-radius: 10px; padding: 10px; font: bold 14px 'Segoe UI';} QPushButton:hover {background-color: #FFC977;} QPushButton:pressed {background-color: #FCB851;}");
    ui->menu->setStyleSheet("QPushButton {background-color: #E4A74C; color: white; border: 2px solid #FCB851; border-radius: 10px; padding: 10px; font: bold 14px 'Segoe UI';} QPushButton:hover {background-color: #FFC977;} QPushButton:pressed {background-color: #FCB851;}");
    ui->salir->setStyleSheet("QPushButton {background-color: #E4A74C; color: white; border: 2px solid #FCB851; border-radius: 10px; padding: 10px; font: bold 14px 'Segoe UI';} QPushButton:hover {background-color: #FFC977;} QPushButton:pressed {background-color: #FCB851;}");
    ui->teclas->setStyleSheet("QPushButton {background-color: #E4A74C; color: white; border: 2px solid #FCB851; border-radius: 10px; padding: 10px; font: bold 14px 'Segoe UI';} QPushButton:hover {background-color: #FFC977;} QPushButton:pressed {background-color: #FCB851;}");

    ui->vidaEnemigo->setVisible(false);
    ui->iconoEnemigo->setVisible(false);
    ui->vidaGoku->setVisible(false);
    ui->iconoGoku->setVisible(false);
    ui->labelEsferas->setVisible(false);
    ui->conteoEsferas->setVisible(false);
    ui->menu->setVisible(false);

    timerEscena = new QTimer(this);
    connect(timerEscena, &QTimer::timeout, this, &MainWindow::actualizar);

    gestorSonido = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    gestorSonido->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.6);
    gestorSonido->setSource(QUrl("qrc:/audios/Menu.mp3"));
    gestorSonido->setLoops(-1);
    gestorSonido->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nivel1_clicked()
{
    id = 1;
    contadorEsferas = 0;
    esferasRecolectadas = 0;
    ui->conteoEsferas->setText(QString('0'));

    gestionarSonido("qrc:/audios/Nivel1.mp3",-1);
    gestionarLabelsNiveles(true);

    // Fondo dinamico
    fondo.load(":/sprites/backgrounds/level1.png");
    fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    fondo1 = new QGraphicsPixmapItem(fondo);
    fondo = fondo.transformed(QTransform().scale(-1, 1));
    fondo2 = new QGraphicsPixmapItem(fondo);
    fondo1->setPos(0, 0);
    fondo2->setPos(fondo1->pixmap().width(), 0);
    escena->addItem(fondo1);
    escena->addItem(fondo2);

    goku = new Goku(0, 400, ui->graphicsView, enemigos,id);
    escena->addItem(goku);
    goku->setFocus();

    // Plataformas
    plataformas[0] = new Plataforma(350, 425);
    escena->addItem(plataformas[0]);
    ultimaXPlataforma = 350;
    for(unsigned char i = 1; i < 8; i++){
        plataformas[i] = new Plataforma(ultimaXPlataforma + 600,QRandomGenerator::global()->bounded(250, 426));
        escena->addItem(plataformas[i]);
        ultimaXPlataforma = plataformas[i]->getX();
    }

    // Esferas
    esferas.fill(nullptr);

    timerFondo = new QTimer(this);
    connect(timerFondo, &QTimer::timeout, this, [=]() {
        const int velocidadMovimiento = 6;

        fondo1->setX(fondo1->x() - velocidadMovimiento);
        fondo2->setX(fondo2->x() - velocidadMovimiento);

        if (fondo1->x() <= -fondo1->pixmap().width()) {
            fondo1->setX(fondo2->x() + fondo2->pixmap().width());
        }
        if (fondo2->x() <= -fondo2->pixmap().width()) {
            fondo2->setX(fondo1->x() + fondo1->pixmap().width());
        }

        for (auto plataforma : plataformas)
            plataforma->mover();

        for(auto esfera : esferas)
            if(esfera) esfera->mover();

        bool colisionConPlataforma = false;

        for (auto plataforma : plataformas) {
            if (goku->collidesWithItem(plataforma)) {
                QRectF gokuRect = goku->sceneBoundingRect();
                QRectF plataformaRect = plataforma->sceneBoundingRect();

                if (goku->getVelY() > 0 && gokuRect.bottom() >= plataformaRect.top() && gokuRect.top() < plataformaRect.top()) {
                    goku->setY(plataformaRect.top() - gokuRect.height());
                    goku->setVelY(0);
                    goku->setVelX(0);
                    goku->setSalto(false);
                    colisionConPlataforma = true;
                    break;
                }

                if (goku->getVelY() < 0 && gokuRect.top() <= plataformaRect.bottom() && gokuRect.bottom() > plataformaRect.bottom()) {
                    goku->setY(plataformaRect.bottom());
                    goku->setVelY(0);
                    break;
                }
            }
        }
        if (!colisionConPlataforma && !goku->getSalto() && (goku->getY() + 190 < 450)) goku->setDebeCaer(true);
    });

    timerObstaculos = new QTimer(this);
    connect(timerObstaculos, &QTimer::timeout, this, [=](){
        qreal y = QRandomGenerator::global()->bounded(0,490);
        Obstaculo* nuevo = new Obstaculo( [this](Obstaculo* p) { eliminarObstaculo(p); }, goku, 450, 1400, y, 0, 0,0,id);
        proyectiles.push_back(nuevo);
        escena->addItem(nuevo);
        nuevo->setPos(1400, y);
        nuevo->mover();
    });

    timerObstaculos->start(3000);
    timerFondo->start(15);
    timerEscena->start(32);

    connect(goku, &Goku::actualizarVida, this, [=](int vida) {ui->vidaGoku->setValue(vida);});
    connect(goku, &Goku::derrotado, this, &MainWindow::perdio);
}


void MainWindow::on_nivel2_clicked()
{
    id = 2;
    gestionarSonido("qrc:/audios/Nivel2.mp3",-1);
    gestionarFondo(":/sprites/backgrounds/level2.png");
    gestionarLabelsNiveles(false);

    goku = new Goku(0, 450, ui->graphicsView, enemigos,id);
    escena->addItem(goku);
    goku->setFocus();

    Enemigo* enemigo = new Enemigo(1200, 100, proyectiles, goku, [this](Obstaculo* p) { eliminarObstaculo(p); },id);
    escena->addItem(enemigo);
    enemigos.push_back(enemigo);

    connect(goku, &Goku::actualizarVida, this, [=](int vida) {ui->vidaGoku->setValue(vida);});
    connect(goku, &Goku::derrotado, this, &MainWindow::perdio);
    for(auto enemigo : enemigos){
        connect(enemigo, &Enemigo::actualizarVida, this, [=](int vida) {ui->vidaEnemigo->setValue(vida);});
        connect(enemigo, &Enemigo::derrotado, this, &MainWindow::gano);
    }
    timerEscena->start(32);
}

void MainWindow::actualizar(){
    escena->update();

    if(id == 1){
        for(auto plataforma : plataformas){
            if (plataforma->getX() + 150 < 0) {
                plataforma->setX(ultimaXPlataforma + 600);
                plataforma->setY(QRandomGenerator::global()->bounded(200, 401));
                plataforma->setPos(plataforma->getX(),plataforma->getY());
                plataforma->setReposicionado(true);

                if (contadorEsferas < 7 && (QRandomGenerator::global()->bounded(0, 100) < 40) && !plataforma->getTieneEsfera()) {
                    esferas[contadorEsferas] = new Esfera(contadorEsferas + 1, plataforma->getX() + 60, plataforma->getY() - 45, goku, plataforma);
                    escena->addItem(esferas[contadorEsferas]);
                    plataforma->setTieneEsfera(true);
                    connect(esferas[contadorEsferas], &Esfera::esferaRecolectada, this, [=](){
                        esferasRecolectadas++;
                        ui->conteoEsferas->setText(QString::number(esferasRecolectadas));
                        if(esferasRecolectadas == 7){
                            QTimer::singleShot(0, this, [=](){
                                timerFondo->stop();
                                gano();
                            });
                        }
                    });
                    contadorEsferas++;
                }
            }
            ultimaXPlataforma = plataforma->getX();
        }
    }
}

void MainWindow::eliminarObstaculo(Obstaculo* p) {
    proyectiles.remove(p);
    p->deleteLater();
}

void MainWindow::finalizarNivel() {
    if(timerEscena) timerEscena->stop();
    if(timerFondo){
        timerFondo->stop();
        delete timerFondo;
        timerFondo = nullptr;
    }
    if(timerObstaculos){
        timerObstaculos->stop();
    delete timerObstaculos;
    timerObstaculos = nullptr;
    }

    if(fondo1){
        delete fondo1;
        fondo1 = nullptr;
    }
    if(fondo2){
        delete fondo2;
        fondo2 = nullptr;
    }

    ui->vidaEnemigo->setVisible(false);
    ui->iconoEnemigo->setVisible(false);
    ui->vidaGoku->setVisible(false);
    ui->iconoGoku->setVisible(false);
    ui->labelEsferas->setVisible(false);
    ui->conteoEsferas->setVisible(false);

    for (auto proyectil : proyectiles) {
        if (proyectil && escena->items().contains(proyectil)) {
            escena->removeItem(proyectil);
            proyectil->deleteLater();
        }
    }
    proyectiles.clear();

    for (auto enemigo : enemigos) {
        if (enemigo && escena->items().contains(enemigo)) {
            escena->removeItem(enemigo);
            enemigo->deleteLater();
        }
    }
    enemigos.clear();

    if (goku && escena->items().contains(goku)) {
        escena->removeItem(goku);
        goku->deleteLater();
        goku = nullptr;
    }

    for(auto esfera : esferas){
        if(esfera && escena->items().contains(esfera)){
            escena->removeItem(esfera);
            esfera->deleteLater();
        }
    }

    esferas.fill(nullptr);

    for(auto plataforma: plataformas){
        if(plataforma && escena->items().contains(plataforma)){
            escena->removeItem(plataforma);
            plataforma->deleteLater();
        }
    }

    for (auto item : escena->items()) {
        if (item && item->scene() == escena) {
            escena->removeItem(item);
        }
    }
}

void MainWindow::on_teclas_clicked()
{
    ui->vidaEnemigo->setVisible(false);
    ui->iconoEnemigo->setVisible(false);
    ui->vidaGoku->setVisible(false);
    ui->iconoGoku->setVisible(false);
    ui->nivel1->setVisible(false);
    ui->nivel2->setVisible(false);
    ui->teclas->setVisible(false);
    ui->salir->setVisible(false);
    ui->labelEsferas->setVisible(false);
    ui->conteoEsferas->setVisible(false);
    ui->menu->setVisible(true);

    gestionarFondo(":/sprites/backgrounds/keys.png");
    ui->menu->move(170,610);
}


void MainWindow::on_salir_clicked()
{
    this->close();
}

void MainWindow::on_menu_clicked()
{
    gestionarSonido("qrc:/audios/Menu.mp3",-1);
    gestionarFondo(":/sprites/backgrounds/menu.png");

    ui->vidaEnemigo->setVisible(false);
    ui->iconoEnemigo->setVisible(false);
    ui->vidaGoku->setVisible(false);
    ui->iconoGoku->setVisible(false);
    ui->labelEsferas->setVisible(false);
    ui->conteoEsferas->setVisible(false);
    ui->menu->setVisible(false);
    ui->nivel1->setVisible(true);
    ui->nivel2->setVisible(true);
    ui->teclas->setVisible(true);
    ui->salir->setVisible(true);
}

void MainWindow::gano(){
    finalizarNivel();

    gestionarSonido("qrc:/audios/NivelGano.mp3",1);
    gestionarFondo(":/sprites/backgrounds/gano.png");
    ui->menu->move(170, 610);
    ui->menu->setVisible(true);
}

void MainWindow::perdio(){
    finalizarNivel();

    gestionarSonido("qrc:/audios/NivelPerdio.mp3",1);
    gestionarFondo(":/sprites/backgrounds/perdio.png");

    ui->menu->move(650,300);
    ui->menu->setVisible(true);
}

void MainWindow::gestionarSonido(QString url, int loop){
    if(gestorSonido->isPlaying()) gestorSonido->stop();
    gestorSonido->setSource(QUrl(url));
    gestorSonido->setLoops(loop);
    gestorSonido->play();
}

void MainWindow::gestionarFondo(QString url){
    fondo.load(url);
    fondo = fondo.scaled(1400, 730, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *bgImage = new QGraphicsPixmapItem(fondo);
    bgImage->setPos(0, 0);
    ui->graphicsView->scene()->addItem(bgImage);
}

void MainWindow::gestionarLabelsNiveles(bool modo){
    ui->iconoGoku->setVisible(true);
    ui->vidaGoku->setVisible(true);
    ui->vidaEnemigo->setVisible(!modo);
    ui->iconoEnemigo->setVisible(!modo);
    ui->labelEsferas->setVisible(modo);
    ui->conteoEsferas->setVisible(modo);
    ui->nivel1->setVisible(false);
    ui->nivel2->setVisible(false);
    ui->teclas->setVisible(false);
    ui->salir->setVisible(false);
    ui->menu->setVisible(false);

    ui->vidaEnemigo->setValue(255);
    ui->vidaGoku->setValue(255);
}
