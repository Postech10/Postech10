#include "GoldTower.h"
#include "Game.h"

extern Game* game;

GoldTower::GoldTower()
{
    TargetNum = 1;
    TowerCode = GOLD;
    Hp = 100;
    AttackPower = 30;
    DefensivePower = 20;
    GoldPower = 10;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    setPixmap(QPixmap(":/images/Icon_IME.bmp"));     //set pic
}

void GoldTower::Attack()
{
    GoldBullet *bullet = new GoldBullet(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

void GoldTower::SetGoldPower(int gold)
{
    GoldPower = gold;
}

int GoldTower::GetGoldPower()
{
    return GoldPower;
}
