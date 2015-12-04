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
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

