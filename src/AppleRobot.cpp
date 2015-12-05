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
    set_image(QString::fromStdString("://images/Animation_AppleDeathMachine.bmp"));
    set_state(CALM);
}

void AppleRobot::Attack()
{
    SplashLaser *bullet = new SplashLaser(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
    set_state(ATTACK);
}

