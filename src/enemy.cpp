#include "enemy.h"
#include <QDebug>
#include <QGraphicsScene>

#define width 500
#define height 500



Enemy::Enemy(int level)
{
    currentLevel = level;

    int xLoc[10] = {70,45,20,20,50,80,80,80,45,20};
    int yLoc[10] = {80,80,80,60,60,60,35,10,10,10};

    for(int i=0;i<10;i++){
        path[i][0] = xLoc[i]*width/100;
        path[i][1] = yLoc[i]*height/100;
    }
    /*path[0][0]=70*width/100;           //path represented by points 0->1.....
    path[0][1]=80*height/100;
    path[1][0]=45*width/100;
    path[1][1]=80*height/100;
    path[2][0]=20*width/100;
    path[2][1]=80*height/100;
    path[3][0]=20*width/100;
    path[3][1]=60*height/100;
    path[4][0]=50*width/100;
    path[4][1]=60*height/100;
    path[5][0]=80*width/100;
    path[5][1]=60*height/100;
    path[6][0]=80*width/100;
    path[6][1]=35*height/100;
    path[7][0]=80*width/100;
    path[7][1]=10*height/100;
    path[8][0]=45*width/100;
    path[8][1]=10*height/100;
    path[9][0]=20*width/100;
    path[9][1]=10*height/100; */
    currentPath=-1;     //not yet on path

    clockRate=10000/(60+currentLevel);   //different velocity according to level

    life=1;
    Hp=(currentLevel/10+1)*50;
    DefensivePower=1;

    if(currentLevel%10!=0)
        this->HideAttackRange();

    setPicture();

    setPos(path[0][0],path[0][1]);

    //move according to signal
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

}

void Enemy::IsPoisonedBy(int power)
{
    poisonedTime=0;
    poisonTime = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(IsHitByP(power)));
    timer->start(clockRate);
}

void Enemy::IsSlowedBy()
{
    slowedState=0;
    slowTime = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(changeClockRate()));
    timer->start(1000);
}

void Enemy::IsHitBy(int power)
{
      BattleObject::IsHitBy(power);   //decrease Hp
      if(Hp<=0){
          scene()->removeItem(this);
          delete timer;
      }

}

void Enemy::startMovement()
{
    timer->start(50);
}

void Enemy::setPicture()     //Hp AttackPower DefensePower
{
    int n = currentLevel;

    switch(n/10){
    case 0:
        if(n%10) setPixmap(QPixmap(":/images/Mechanical.bmp"));
        else     setPixmap(QPixmap(":/images/Enemy2.png"));
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
        x_move=(path[currentPath+1][0]-path[currentPath][0])/50;
        y_move=(path[currentPath+1][1]-path[currentPath][1])/50;
    }

    setPos(x()+x_move, y()+y_move);

    if((x()== path[9][0]) && (y()==path[9][1])){                 //end point
        qDebug() << "Fail to remove enemy";
        scene()->removeItem(this);
        delete timer;
    }

}

void Enemy::IsHitByP(int power)     //poisoned
{
    BattleObject::IsHitBy(power);   //decrease Hp
    poisonedTime+=clockRate;        //calculate poisoned time

    if(Hp<=0){
        delete poisonTime;
        scene()->removeItem(this);
        delete timer;
    }

    if(poisonedTime>500)            //after specific time, released from poison
        delete poisonTime;
}

void Enemy::changeClockRate()
{
    delete timer;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    if (slowedState=0){
        timer->start(2*clockRate);    //slowed, doubled clockrate
        slowedState=1;
    }
    else {
        timer->start(clockRate);      //recovered from slow state
        slowedState=0;
        delete slowTime;
    }

}
