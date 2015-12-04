#include "PoisonTower.h"
#include "Game.h"

extern Game* game;

PoisonTower::PoisonTower()
{
    TargetNum = 1;
    TowerCode = POISON;
    Hp = 100;
    AttackPower = 30;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    setPixmap(QPixmap(":/images/Icon_Chemical.bmp"));     //set pic
}

void PoisonTower::Attack()
{
    PoisonBullet *bullet = new PoisonBullet(AttackPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

