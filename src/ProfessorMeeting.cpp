#include "ProfessorMeeting.h"
#include "Game.h"

extern Game* game;

ProfessorMeeting::ProfessorMeeting()
{
    TargetNum = 1;
    TowerCode = PROF;
    Hp = 100;
    SlowPower = 20;
    AttackPower = 40;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString("://images/Animation_Session.bmp"));
    set_state(CALM);
}

void ProfessorMeeting::Attack()
{
    PMBullet *bullet = new PMBullet(AttackPower,SlowPower);
    bullet->Activated(true);
    bullet->setPos(x()+32,y()+32);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+32,y()+32),QPointF(Target->x()+32,Target->y()+32));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
    set_state(ATTACK);
}

