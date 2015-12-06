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
    QTimer* timer;          //path
    QTimer* poisonTime;     //In poisoned state, hit timing
    QTimer* slowTime;       //slowed->recovered timing
    float path[10][2];      //x,y
    int currentPath;        //current path : between path[i][i] & path[i+1][i+1
    int clockRate;          //moving clockrate
    float x_move;           //move in one clock
    float y_move;           //move in one clock
    int currentLevel;       //level
    void setPicture();      //according to level set different enemy's picture
    int life;               //Enemy alive:1, not:0
    float poisonedTime;     //elapsed time from poisoning point
    int slowedState;        //slowed:1, not:0
    int poisonedState;      //poisoned:1, not:0
    int poisonPower;        //Attackpower in poisoned state
    int poison_gold;        //Amount of received gold, when killed by goldPoisonTower
    int reach;              //Arrive at Final point(path[9][9]):1, not:0




public:
    Enemy(int level=1);                 //constructor, Initailizind
    int DieOrNot(){ return !life; }     //Die=0, not=1
    void IsPoisonedBy(int);             //called when attack by poison tower
    void IsGoldPoisonedBy(int, int);    //called when attack by goldPoisonTower
    void IsSlowedBy(int);               //called when attack by slow tower
    void IsHitBy(int);                  //called when attacked
    void startMovement();               //start to move inside a map
    void die(){life=0; this->HideAttackRange();}        //exist for attackable enemy, called when attackableEnemy die
    void setClockRate(int clock){clockRate=clock;}      //set clockRate
    int getLevel(){return currentLevel;}                //return level information
    ~Enemy();                           //destructor
public slots:
    void move();                      //go through path
    void IsHitByP(int p=0);           //decrease Hp, when poisoned by tower
    void changeClockRate();           //change the move speed of enemy, when attacked by slow Tower
};


#endif // ENEMY_H

