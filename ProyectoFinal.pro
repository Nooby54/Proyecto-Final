QT += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigo.cpp \
    esfera.cpp \
    goku.cpp \
    kamehameha.cpp \
    main.cpp \
    mainwindow.cpp \
    obstaculo.cpp \
    personaje.cpp \
    plataforma.cpp

HEADERS += \
    enemigo.h \
    esfera.h \
    goku.h \
    kamehameha.h \
    mainwindow.h \
    obstaculo.h \
    personaje.h \
    plataforma.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    audios.qrc \
    backgrounds.qrc \
    sprites.qrc
