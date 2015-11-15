#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image 설정
    SetAttackPower(attack);
    GoldPower = gold;
}

