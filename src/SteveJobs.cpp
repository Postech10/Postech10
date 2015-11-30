#include "SteveJobs.h"
#include "Game.h"

extern Game* game;

SteveJobs::SteveJobs()
{
    TargetNum = 0;
    TowerCode = JOBS;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = false;                  //this will be changed for balance
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
    this->HideAttackRange();
}

void SteveJobs::Activated(bool active)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(IncGold()));
    if(active)
        timer->start(1/AttackSpeed);
    else
        timer->stop();
}

void SteveJobs::IncGold()
{
    game->set_money(game->get_money()+AttackPower);                      //in this part, attackpower means gold inc power
}

