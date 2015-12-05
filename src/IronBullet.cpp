#include "IronBullet.h"

IronBullet::IronBullet(int attack, int gold)
{
    QPixmap* image = new QPixmap("://images/Bullet_Iron.bmp");
    image->setMask(image->createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(attack);
    GoldPower = gold;
}

