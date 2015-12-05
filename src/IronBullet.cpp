#include "IronBullet.h"
#include <QBitmap>

IronBullet::IronBullet(int attack, int gold)
{
    QPixmap image("://images/Bullet_Iron.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(attack);
    GoldPower = gold;
}

