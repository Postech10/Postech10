#include "SteveJobs.h"

SteveJobs::SteveJobs()
{
    TargetNum = 0;
    TowerCode = JOBS;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = false;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    setPixmap(QPixmap(":/images/stevejobs.png"));     //사진설정
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
    game->set_money(game->get_money()+AttackPower);                      //여기선 AttackPower가 골드증가량..
}

