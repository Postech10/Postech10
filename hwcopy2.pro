#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T12:26:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hwcopy2
TEMPLATE = app


SOURCES += main.cpp \
    BuildTowerIcon.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Tower.cpp \
    upgrade_button.cpp \
    fusion_button.cpp

HEADERS  += \
    BuildTowerIcon.h \
    Bullet.h \
    Enemy.h \
    Game.h \
    Tower.h \
    upgrade_button.h \
    fusion_button.h

RESOURCES += \
    pic.qrc
