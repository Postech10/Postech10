#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include<QWidget>
#include "BattleObject.h"
#include "soundobject.h"
#include <QTimer>

class Enemy : public BattleObject{
Q_OBJECT
private:

    QTimer* poisonTime;     //poisoned->recovered
    QTimer* slowTime;       //slowed->recovered
    float path[10][2];      //x,y
    int currentPath;        //show current path
    int clockRate;
    float x_move;           //move in one clock
    float y_move;           //move in one clock
    int currentLevel;       //level
    void setPicture();      //according to level set different enemy's picture
    int life;               //DiedOrNot
    float poisonedTime;     //elapsed time from poisoning point
    int slowedState;        //slowed:1, not:0
    int poisonedState;
    int poisonPower;
    int poison_gold;
    int reach;
protected:
    QTimer* timer;          //path


public:
    Enemy(int level=1);               //constructor
    int DieOrNot(){ return !life; }    //Die=0, not=1
    void IsPoisonedBy(int);           //called when attack by poison tower
    void IsGoldPoisonedBy(int, int);
    void IsSlowedBy(int);                //called when attack by slow tower
    void IsHitBy(int);               //called when attacked
    void startMovement();
    void die(){life=0; this->HideAttackRange();}
    void setClockRate(int clock){clockRate=clock;}
    int getLevel(){return currentLevel;}
    ~Enemy();
public slots:
    void move();                      //go through path
    void IsHitByP(int p=0);               //decrease Hp, when poisoned by tower
    void changeClockRate();           //change the move speed of enemy
};


#endif // ENEMY_H

