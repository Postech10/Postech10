#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T22:46:08
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sangjin
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += $$PWD/include/
OBJECTS_DIR = $$PWD/obj
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rss
DESTDIR = $$PWD/bin


SOURCES += \
    src/upgrade_button.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/fusion_button.cpp \
    src/enemycontrol.cpp \
    src/enemy.cpp \
    src/button.cpp \
    src/attackableenemy.cpp \
    src/Wave_Generator.cpp \
    src/Upgrades.cpp \
    src/TutorRobot.cpp \
    src/TripleMajorSenior.cpp \
    src/Tower.cpp \
    src/SteveJobs.cpp \
    src/SplashTower.cpp \
    src/SplashPoisonBullet.cpp \
    src/SplashLaser.cpp \
    src/SplashBullet.cpp \
    src/SlowTower.cpp \
    src/SlowBullet.cpp \
    src/ProfessorMeeting.cpp \
    src/PoisonTower.cpp \
    src/PoisonBullet.cpp \
    src/PMBullet.cpp \
    src/MetalEngSenior.cpp \
    src/JobsBiography.cpp \
    src/IronBullet.cpp \
    src/GoldTower.cpp \
    src/GoldBullet.cpp \
    src/Game.cpp \
    src/ChemEngSenior.cpp \
    src/ChainTower.cpp \
    src/CESBullet.cpp \
    src/Bullet.cpp \
    src/BuildTowerIcon.cpp \
    src/BattleObject.cpp \
    src/AppleRobot.cpp \
    src/soundobject.cpp \
    src/animatedbattleobject.cpp \
    src/control_animation.cpp \
    src/bullet_enemy.cpp

HEADERS  += \
    include/upgrade_button.h \
    include/mainwindow.h \
    include/fusion_button.h \
    include/enemycontrol.h \
    include/enemy.h \
    include/button.h \
    include/attackableenemy.h \
    include/Wave_Generator.h \
    include/Upgrades.h \
    include/TutorRobot.h \
    include/TripleMajorSenior.h \
    include/Tower.h \
    include/SteveJobs.h \
    include/SplashTower.h \
    include/SplashPoisonBullet.h \
    include/SplashLaser.h \
    include/SplashBullet.h \
    include/SlowTower.h \
    include/SlowBullet.h \
    include/ProfessorMeeting.h \
    include/PoisonTower.h \
    include/PoisonBullet.h \
    include/PMBullet.h \
    include/MetalEngSenior.h \
    include/JobsBiography.h \
    include/IronBullet.h \
    include/GoldTower.h \
    include/GoldBullet.h \
    include/Game.h \
    include/ChemEngSenior.h \
    include/ChainTower.h \
    include/CESBullet.h \
    include/Bullet.h \
    include/BuildTowerIcon.h \
    include/BattleObject.h \
    include/AppleRobot.h \
    include/soundobject.h \
    include/animatedbattleobject.h \
    include/control_animation.h \
    include/bullet_enemy.h

RESOURCES += \
    resources/sources.qrc \

