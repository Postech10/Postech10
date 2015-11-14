#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/iron_bullet.png"));          //image 설정
    SetAttackPower(power);
    GoldPower = gold;
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //일정 시간마다 움직임
    move_timer->start(30);
}

