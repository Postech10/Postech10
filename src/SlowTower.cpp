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
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
}

void SlowTower::Attack()
{
    SlowBullet *bullet = new SlowBullet(SlowPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

void SlowTower::SetSlowPower(int slow)
{
    SlowPower = slow;
}

int SlowTower::GetSlowPower()
{
    return SlowPower;
}

