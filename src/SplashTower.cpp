#include "SplashTower.h"
#include "Game.h"

extern Game* game;


SplashTower::SplashTower()
{
    TargetNum = 1;
    TowerCode = SPLASH;
    Hp = 100;
    AttackPower = 15;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString("://images/Animation_Mechanical.bmp"));
    set_state(CALM);
}


void SplashTower::Attack()
{
    SplashBullet *bullet = new SplashBullet(AttackPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
    set_state(ATTACK);
}
