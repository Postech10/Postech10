#pragma once
#ifndef BULLET
#define BULLET

#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>
#include <QtMath>
#include <typeinfo>
#include "BattleObject.h"
#include "enemy.h"
#include "soundobject.h"

#define STEP_SIZE 30                //default STEP_SIZE

class Bullet: public QObject, public QGraphicsPixmapItem, public SoundObject{
    Q_OBJECT
public:
    Bullet();
    virtual ~Bullet();
    Bullet(int);           //constructor, int means bullet's power(?)
    void SetAttackPower(int);
    int GetAttackPower();
    void Activated(bool);
public slots:
    virtual void move();        //bullet move method
    virtual void callDestructor();
protected:
    int AttackPower;        //Bullet power
    QTimer* move_timer;
};

#endif // BULLET

