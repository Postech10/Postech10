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
    Game.cpp \
    Tower.cpp \
    upgrade_button.cpp \
    Wave_Generator.cpp \
    Fusion_Button.cpp \
    Button.cpp

HEADERS  += \
    BuildTowerIcon.h \
    Bullet.h \
    Enemy.h \
    first.h \
    Game.h \
    Tower.h \
    upgrade_button.h \
    Wave_Generator.h \
    Fusion_Button.h \
    Button.h

RESOURCES += \
    sources.qrc

FORMS += \
    form.ui
