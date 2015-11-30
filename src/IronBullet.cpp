#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SetAttackPower(attack);
    GoldPower = gold;
}

