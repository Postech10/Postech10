#include "enemy.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QString>
#include <QDebug>

#define width 640
#define height 640


extern Game* game;
Enemy::Enemy(int level)
{
    currentLevel = level;

    int xLoc[10] = {70,45,20,20,50,80,80,80,45,20};
    int yLoc[10] = {80,80,80,60,60,60,35,10,10,10};

    for(int i=0;i<10;i++){      //the path enemy should go through
        path[i][0] = xLoc[i]*width/100+64;
        path[i][1] = yLoc[i]*height/100+45;
    }

    currentPath=-1;     //not yet on path


    life=1;     //initialization
    Hp=30+currentLevel*3;
    DefensivePower=2;
    slowedState=0;
    poisonedState=0;
    poisonPower=0;
    reach=0;

    slowTime = nullptr;
    poisonTime = nullptr;
    timer = nullptr;
    hpBar = nullptr;

    if(currentLevel%10!=0)      //if non-attackable, no need of attack range
        this->HideAttackRange();

    setPicture();       //set proper enemy picture

    setPos(path[0][0],path[0][1]);  //one first position in the path



    timer = new QTimer();       //moving timer
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));


}

void Enemy::IsPoisonedBy(int power)     //attacked by poisonTower
{
    IsHitBy(power*3/5);     //First hit by poison
    if(Hp>0){
    if( poisonedState==1){  //if already poisoned state, delete poisonTime to re-poisoning
        delete poisonTime;
        poisonTime=nullptr;
    }
    poisonedState=1;    //poison state initialization
    poisonedTime=0;
    poisonPower=power*3/5;
    poison_gold=0;
    hpBar->setBrush(QBrush(Qt::green)); //if poisoned, hpBar become green
    poisonTime = new QTimer();  //to hit constantly, set timer
    connect( poisonTime, SIGNAL(timeout()), this, SLOT(IsHitByP()));     //렉트 사운드
    poisonTime->start(1000);
    }
}

void Enemy::IsGoldPoisonedBy(int power, int gold)       //attacked by goldPoisonTower, similar to poisontower
{
    IsHitBy(power*3/5);
    if(Hp>0){
    if( poisonedState==1){
        delete poisonTime;
        poisonTime = nullptr;
    }

    poisonedState=1;
    poisonedTime=0;
    poisonPower=power*3/5;
    poison_gold=gold;       //but, it can earn gold additionally!
    hpBar->setBrush(QBrush(Qt::yellow));    //if goldPoisoned, hpBar becomes yellow
    poisonTime = new QTimer();
    connect( poisonTime, SIGNAL(timeout()), this, SLOT(IsHitByP()));
    poisonTime->start(1000);
    }
}

void Enemy::IsSlowedBy(int power)   //
{
    for(int i=0; i<2; i++)      //if slow attacked repeatly, enemy cannot move. -> move a little when hit by slow attack
        move();
    if (slowedState==1){    //if already slowed state, delete slowtime to reset the slow timer
        delete slowTime;
        slowTime = nullptr;
    }

    slowedState=1;      //slowed state
    delete timer;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(clockRate/5*power);    //slowed movement

    slowTime = new QTimer();
    connect(slowTime, SIGNAL(timeout()), this, SLOT(changeClockRate()));
    slowTime->start(5000);      //after 5 sec, return to original movement speed
}

void Enemy::IsHitBy(int power)      //attacked by tower
{
      if(poisonedState==1)      //for poisoned state attack, decrease Hp
          Hp = Hp - poisonPower/DefensivePower;

      Hp = Hp - (power/DefensivePower);   //decrease Hp


      if(Hp<=0){        //enemy die
          life=0;
          game->set_money(game->get_money()+1);
          game->RenewEnemyNum(true);
          scene()->removeItem(hpBar);
          scene()->removeItem(this);
          delete timer;
          timer= nullptr;
          delete hpBar;
          hpBar=nullptr;
          if(slowTime!=nullptr){
              delete slowTime;
              slowTime = nullptr;
          }
          if(poisonTime!=nullptr){
              delete poisonTime;
              poisonTime = nullptr;
          }
      }
      else      //if enemy is alive, set Hpbar again
          cutHpbar();


}

void Enemy::startMovement() //start to move in the map
{
    clockRate=50 - 5*(currentLevel/10);
    setHpbar();
    timer->start(clockRate);
}



Enemy::~Enemy() //destructor
{
    if (slowTime!=nullptr)
        delete slowTime;
    if(poisonTime!=nullptr)
        delete poisonTime;
    if(timer!=nullptr)
        delete timer;
    if(hpBar!=nullptr)
        delete hpBar;

}

void Enemy::setPicture()     //set different enemy picture according to level
{
    int n = currentLevel;

    switch((n-1)/10){       //use function in animation class, animation play
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

    }
    if(n == 41){
        set_image(QString::fromStdString(":/images/Animation_Professor.bmp"));
        set_state(CALM);
    }

}

void Enemy::move()      //move along the path
{   //arrive a point
    if ((((x()>= (path[currentPath+1][0]-0.2)))&& (x()<= (path[currentPath+1][0]+0.2))) && ((y()>= (path[currentPath+1][1]-0.2))&& (y()<= (path[currentPath+1][1]+0.2)))){
        currentPath++;
        x_move=(path[currentPath+1][0]-path[currentPath][0])/(width/10);    //set step(both x direction, y direction)
        y_move=(path[currentPath+1][1]-path[currentPath][1])/(height/10);
    }

    setPos(x()+x_move, y()+y_move);     //move in step
    hpBar->setPos(x()+x_move, y()-20+y_move);   //hpBar follows enemy

    if((x()== path[9][0]) && (y()==path[9][1])){                 //arrive end point(end of the path)
        playSound("LifeLost");

        reach=1;
        game->SetLife(game->GetLife()-10);      //decrease life

        game->RenewEnemyNum(false);


        game->scene->removeItem(hpBar);

        game->scene->removeItem(this);
        delete timer;
        timer=nullptr;
        delete hpBar;
        hpBar=nullptr;
    }

}

void Enemy::IsHitByP(int power)     //at poisoned state
{   if(reach==0){
    poisonedTime+=1000;

    if(Hp<=0){
        if(poisonTime!=nullptr){
        delete poisonTime;      //enemy dead
        poisonTime=nullptr;
        }
    }
    else if(poisonedTime>2500){            //after specific time, released from poison
        hpBar->setBrush(QBrush(Qt::red));   //back to normal hpBar
        poisonedState=0;
        poison_gold=0;
        if(poisonTime!=nullptr){
        delete poisonTime;
        poisonTime=nullptr;
        }
    }
    else if (reach==0){     //possible to be attacked
        IsHitBy(power);     //attacked
        if (Hp<=0)
            game->set_money(game->get_money()+poison_gold); //get gold, dead by goldPoisonTower
    }
    }

}

void Enemy::changeClockRate()   //back to normal movement speed
{
    if(reach==0){
    delete timer;
    delete slowTime;
    slowTime=nullptr;
    slowedState=0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(clockRate);      //recovered from slow state
    }
}

