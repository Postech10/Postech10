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
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
}

void ProfessorMeeting::Attack()
{
    PMBullet *bullet = new PMBullet(AttackPower,SlowPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

