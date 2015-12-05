#include "SlowTower.h"
#include "Game.h"

extern Game* game;

SlowTower::SlowTower()
{
    TargetNum = 1;
    TowerCode = SLOW;
    Hp = 100;
    SlowPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString("://images/Animation_SMP.bmp"));
    set_state(CALM);
}

void SlowTower::Attack()
{
    SlowBullet *bullet = new SlowBullet(SlowPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
    set_state(ATTACK);
}

void SlowTower::SetSlowPower(int slow)
{
    SlowPower = slow;
}

int SlowTower::GetSlowPower()
{
    return SlowPower;
}

