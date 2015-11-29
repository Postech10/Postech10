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

#define STEP_SIZE 30                //湲곕낯?쇰줈 ?대넃? STEP_SIZE

class Bullet: public QObject, public QGraphicsPixmapItem, public SoundObject{
    Q_OBJECT
public:
    Bullet();
    virtual ~Bullet();
    Bullet(int);           //constructor, int??bullet???뚭눼???)???삵븿
    void SetAttackPower(int);
    int GetAttackPower();
    void Activated(bool);
public slots:
    virtual void move();        //bullet move method
protected:
    int AttackPower;        //Bullet???뚭눼??
    QTimer* move_timer;
};

#endif // BULLET

