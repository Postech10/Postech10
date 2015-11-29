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

#define STEP_SIZE 30                //기본으로 해놓은 STEP_SIZE

class Bullet: public QObject, public QGraphicsPixmapItem, public SoundObject{
    Q_OBJECT
public:
    Bullet();
    virtual ~Bullet();
    Bullet(int);           //constructor, int는 bullet의 파괴력(?)을 뜻함
    void SetAttackPower(int);
    int GetAttackPower();
    void Activated(bool);
public slots:
    virtual void move();        //bullet move method
protected:
    int AttackPower;        //Bullet의 파괴력
    QTimer* move_timer;
};

#endif // BULLET

