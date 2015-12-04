﻿#pragma once
#include "enemy.h"
#include "Game.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QString>

#define width 600
#define height 600


extern Game* game;
Enemy::Enemy(int level)
{
    currentLevel = level;

    int xLoc[10] = {70,45,20,20,50,80,80,80,45,20};
    int yLoc[10] = {80,80,80,60,60,60,35,10,10,10};

    for(int i=0;i<10;i++){
        path[i][0] = xLoc[i]*width/100+80;
        path[i][1] = yLoc[i]*height/100+65;
    }

    currentPath=-1;     //not yet on path

    clockRate=10000/(60+currentLevel);   //different velocity according to level

    life=1;
    Hp=(currentLevel/10+1)*50;
    DefensivePower=1;
    slowedState=0;
    poisonedState=0;

    if(currentLevel%10!=0)
        this->HideAttackRange();

    setPicture();

    setPos(path[0][0],path[0][1]);



    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));


}

void Enemy::IsPoisonedBy(int power)
{
    if( poisonedState==1)
        delete poisonTime;

    poisonedState=1;
    poisonedTime=0;
    hpBar->setBrush(QBrush(Qt::green));
    poisonTime = new QTimer();
    connect( poisonTime, SIGNAL(timeout()), this, SLOT(IsHitByP()));     //렉트 사운드
    poisonTime->start(1000);
}

void Enemy::IsSlowedBy(int power)
{
    if (slowedState==1)
        delete slowTime;

    slowedState=1;

    delete timer;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10*power);    //slowed, doubled clockrate
    qDebug()<<"slOw";

    slowTime = new QTimer();
    connect(slowTime, SIGNAL(timeout()), this, SLOT(changeClockRate()));
    slowTime->start(5000);
}

void Enemy::IsHitBy(int power)
{

      Hp = Hp - power/DefensivePower;   //decrease Hp


      if(Hp<=0){
          life=0;
          game->RenewEnemyNum(true);
          scene()->removeItem(hpBar);
          scene()->removeItem(this);
          if(slowedState==1)
              delete slowTime;
          if(poisonedState==1)
              delete poisonTime;
      }
      else
          cutHpbar();


}

void Enemy::startMovement()
{
    setHpbar();
    timer->start(50);
}



Enemy::~Enemy()
{
    if (Hp>0){
        delete timer;
        delete hpBar;
        if(slowedState==1)
            delete slowTime;
        if(poisonedState==1)
            delete poisonTime;

    }
    //알아서 지워줌
}

void Enemy::setPicture()     //Hp AttackPower DefensePower
{
    int n = currentLevel;

    switch(n/10){
    case 0:
        if(n%10) setPixmap(QPixmap(":/images/Mechanical.bmp"));
        else     setPixmap(QPixmap(":/images/Mechanical.bmp"));
        break;
    case 1:
        if(n%10) setPixmap(QPixmap(":/images/Enemy3.png"));
        else     setPixmap(QPixmap(":/images/Enemy4.png"));
        break;
    case 2:
        if(n%10) setPixmap(QPixmap(":/images/Enemy5.png"));
        else     setPixmap(QPixmap(":/images/Enemy6.png"));
        break;
    case 3:
        if(n%10) setPixmap(QPixmap(":/images/Enemy7.png"));
        else     setPixmap(QPixmap(":/images/Enemy8.png"));
        break;
    }

}

void Enemy::move()
{
    if ((x()== path[currentPath+1][0]) && (y()==path[currentPath+1][1])){
        currentPath++;
        x_move=(path[currentPath+1][0]-path[currentPath][0])/(width/10);
        y_move=(path[currentPath+1][1]-path[currentPath][1])/(height/10);
    }

    setPos(x()+x_move, y()+y_move);
    hpBar->setPos(x()+x_move, y()-20+y_move);

    if((x()== path[9][0]) && (y()==path[9][1])){                 //end point
        qDebug() << "Fail to remove enemy";


        game->SetLife(game->GetLife()-10);
        game->RenewEnemyNum(false);

        scene()->removeItem(hpBar);
        scene()->removeItem(this);

    }

}

void Enemy::IsHitByP(int power)     //poisoned
{

    poisonedTime+=500;
    if(poisonedTime>5000 || Hp<=0){            //after specific time, released from poison
        hpBar->setBrush(QBrush(Qt::red));
        delete poisonTime;
        poisonedState=0;
    }
    else
        IsHitBy(power);

}

void Enemy::changeClockRate()
{
    delete timer;
    delete slowTime;
    slowedState=0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);      //recovered from slow state

    qDebug()<<"fast";
}

