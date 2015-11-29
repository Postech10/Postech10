#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image ?ㅼ젙
    SetAttackPower(attack);
    GoldPower = gold;
}

