
#include "enemy.h"
#include "Game.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QString>

#define width 640
#define height 640


extern Game* game;
Enemy::Enemy(int level)
{
    currentLevel = level;

    int xLoc[10] = {70,45,20,20,50,80,80,80,45,20};
    int yLoc[10] = {80,80,80,60,60,60,35,10,10,10};

    for(int i=0;i<10;i++){
        path[i][0] = xLoc[i]*width/100+64;
        path[i][1] = yLoc[i]*height/100+45;
    }

    currentPath=-1;     //not yet on path

       //different velocity according to level

    life=1;
    Hp=(currentLevel/10+1)*40;
    DefensivePower=2;
    slowedState=0;
    poisonedState=0;
    poisonPower=0;
    reach=0;

    slowTime = nullptr;
    poisonTime = nullptr;
    timer = nullptr;
    hpBar = nullptr;

    if(currentLevel%10!=0)
        this->HideAttackRange();

    setPicture();

    setPos(path[0][0],path[0][1]);



    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));


}

void Enemy::IsPoisonedBy(int power)
{
    if( poisonedState==1){
        delete poisonTime;
        poisonTime=nullptr;
    }

    poisonedState=1;
    poisonedTime=0;
    poisonPower=power;
    poison_gold=0;
    hpBar->setBrush(QBrush(Qt::green));
    poisonTime = new QTimer();
    connect( poisonTime, SIGNAL(timeout()), this, SLOT(IsHitByP()));     //렉트 사운드
    poisonTime->start(1000);
}

void Enemy::IsGoldPoisonedBy(int power, int gold)
{
    if( poisonedState==1){
        delete poisonTime;
        poisonTime = nullptr;
    }

    poisonedState=1;
    poisonedTime=0;
    poisonPower=power;
    poison_gold=gold;
    hpBar->setBrush(QBrush(Qt::yellow));
    poisonTime = new QTimer();
    connect( poisonTime, SIGNAL(timeout()), this, SLOT(IsHitByP()));     //렉트 사운드
    poisonTime->start(1000);
}

void Enemy::IsSlowedBy(int power)
{
    if (slowedState==1){
        delete slowTime;
        slowTime = nullptr;
    }

    slowedState=1;

    delete timer;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(clockRate/5*power);    //slowed, doubled clockrate

    slowTime = new QTimer();
    connect(slowTime, SIGNAL(timeout()), this, SLOT(changeClockRate()));
    slowTime->start(5000);
}

void Enemy::IsHitBy(int power)
{
      if(poisonedState==1)
          Hp = Hp - poisonPower/DefensivePower;

      Hp = Hp - (power/DefensivePower);   //decrease Hp


      if(Hp<=0){
          life=0;
          game->set_money(game->get_money()+1);
          game->RenewEnemyNum(true);
          scene()->removeItem(hpBar);
          scene()->removeItem(this);
          delete timer;
          timer= nullptr;
          delete hpBar;
          hpBar=nullptr;
          if(slowedState==1){
              delete slowTime;
              slowTime = nullptr;
          }
      }
      else
          cutHpbar();


}

void Enemy::startMovement()
{
    clockRate=50 - 5*(currentLevel/10);
    setHpbar();
    timer->start(clockRate);
}



Enemy::~Enemy()
{
    if (slowTime)
        delete slowTime;
    if(poisonTime)
        delete poisonTime;
    if(timer)
        delete timer;
    if(hpBar)
        delete hpBar;

}

void Enemy::setPicture()     //Hp AttackPower DefensePower
{
    int n = currentLevel;

    switch((n-1)/10){
    case 0:
        if(n%9){
            set_image(QString::fromStdString(":/images/Animation_Enemy.bmp"));
            set_state(CALM);
        }
        else{
            set_image(QString::fromStdString(":/images/Animation_Enemy.bmp"));
            set_state(CALM);
        }
        break;
    case 1:
        if(n%9){
            set_image(QString::fromStdString(":/images/Animation_Enemy2.bmp"));
            set_state(CALM);
        }
        else    {
            set_image(QString::fromStdString(":/images/Animation_Enemy2.bmp"));
            set_state(CALM);
        }
        break;
    case 2:
        if(n%9){
            set_image(QString::fromStdString(":/images/Animation_Enemy3.bmp"));
            set_state(CALM);
        }
        else   {
            set_image(QString::fromStdString(":/images/Animation_Enemy3.bmp"));
            set_state(CALM);
        }
        break;
    case 3:
        if(n%9){
            set_image(QString::fromStdString(":/images/Animation_Enemy4.bmp"));
            set_state(CALM);
        }
        else   {
            set_image(QString::fromStdString(":/images/Animation_Enemy4.bmp"));
            set_state(CALM);
        }
        break;
    case 4:
        set_image(QString::fromStdString(":/images/Animation_Enemy4.bmp"));
        set_state(CALM);
        break;
    case 5:
        set_image(QString::fromStdString(":/images/Animation_Professor.bmp"));
        set_state(CALM);


    }

}

void Enemy::move()
{
    if ((((x()>= (path[currentPath+1][0]-0.2)))&& (x()<= (path[currentPath+1][0]+0.2))) && ((y()>= (path[currentPath+1][1]-0.2))&& (y()<= (path[currentPath+1][1]+0.2)))){
        currentPath++;
        x_move=(path[currentPath+1][0]-path[currentPath][0])/(width/10);
        y_move=(path[currentPath+1][1]-path[currentPath][1])/(height/10);
    }

    setPos(x()+x_move, y()+y_move);
    hpBar->setPos(x()+x_move, y()-20+y_move);

    if((x()== path[9][0]) && (y()==path[9][1])){                 //end point
        playSound("LifeLost");

        reach=1;
        game->SetLife(game->GetLife()-10);

        game->RenewEnemyNum(false);


        game->scene->removeItem(hpBar);

        game->scene->removeItem(this);
        delete timer;
        timer=nullptr;
        delete hpBar;
        hpBar=nullptr;
    }

}

void Enemy::IsHitByP(int power)     //poisoned
{

    poisonedTime+=1000;

    if(Hp<=0){
        delete poisonTime;      //끝난경우
        poisonTime=nullptr;
    }
    else if(poisonedTime>3000){            //after specific time, released from poison
        hpBar->setBrush(QBrush(Qt::red));
        poisonedState=0;
        poison_gold=0;
        delete poisonTime;
        poisonTime=nullptr;
    }
    else if (reach==0){
        IsHitBy(power);
        if (Hp<=0)
            game->set_money(game->get_money()+poison_gold);
    }

}

void Enemy::changeClockRate()
{
    delete timer;
    delete slowTime;
    slowedState=0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(clockRate);      //recovered from slow state
}

