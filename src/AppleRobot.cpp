#include "AppleRobot.h"
#include "Game.h"

extern Game* game;

AppleRobot::AppleRobot()
{
    TargetNum = 3;
    TowerCode = APPLE;
    Hp = 100;
    AttackPower = 60;
    DefensivePower = 20;
    GoldPower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //these informations will be changed for balance
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
}

void AppleRobot::Attack()
{
    SplashLaser *bullet = new SplashLaser(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

