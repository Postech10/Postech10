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
    GoldPower = 1;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString("://images/Animation_IME.bmp"));
    set_state(CALM);
}

void GoldTower::Attack()
{
    GoldBullet *bullet = new GoldBullet(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
    set_state(ATTACK);
}

void GoldTower::SetGoldPower(int gold)
{
    GoldPower = gold;
}

int GoldTower::GetGoldPower()
{
    return GoldPower;
}
