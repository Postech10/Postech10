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
    QTimer *timer = new QTimer();                        //반드시 수정이 필요함.. 다른타워와 다른개념이기 때문에
    connect(timer,SIGNAL(timeout()),this,SLOT(IncGold()));
    timer->start(1/AttackSpeed);                         //여기선 AttackSpeed가 골드 증가 시간
                                                         //나중에 알맞게 수정예정
}

void SteveJobs::IncGold()
{
    game->set_money(game->get_money()+AttackPower);                      //여기선 AttackPower가 골드증가량..
}

