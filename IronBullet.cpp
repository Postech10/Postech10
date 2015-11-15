#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/iron_bullet.png"));          //image 설정
    SetAttackPower(attack);
    GoldPower = gold;
}

