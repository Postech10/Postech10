#include "ChemEngSenior.h"
#include "Game.h"

extern Game* game;

ChemEngSenior::ChemEngSenior()
{
    TargetNum = 1;
    TowerCode = CES;
    Hp = 100;
    AttackPower = 40;
    DefensivePower = 20;
    GoldPower = 10;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
}

void ChemEngSenior::Attack()
{
    CESBullet *bullet = new CESBullet(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene

}

