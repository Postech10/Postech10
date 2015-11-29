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
    Attackable = false;                  //珥덇린?ㅼ젙 ?섏쨷??諛몃윴?ㅻ? ?꾪빐 諛붽?嫄곗엫
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //?ъ쭊?ㅼ젙
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
    game->set_money(game->get_money()+AttackPower);                      //?ш린??AttackPower媛 怨⑤뱶利앷???.
}

