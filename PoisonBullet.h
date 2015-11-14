#ifndef POISONBULLET_H
#define POISONBULLET_H

#include "Bullet.h"

class PoisonBullet: public Bullet{
public:
    PoisonBullet(int AttackPower);
public slots:
    void move();
};

#endif // POISONBULLET_H
