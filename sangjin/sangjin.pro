#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T22:46:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sangjin
TEMPLATE = app


SOURCES += main.cpp\
    BuildTowerIcon.cpp \
    Bullet.cpp \
    Enemy.cpp \
    fusion_button.cpp \
    Game.cpp \
    Tower.cpp \
    upgrade_button.cpp

HEADERS  += \
    BuildTowerIcon.h \
    Bullet.h \
    Enemy.h \
    first.h \
    fusion_button.h \
    Game.h \
    Tower.h \
    upgrade_button.h

RESOURCES += \
    sources.qrc

FORMS += \
    form.ui
