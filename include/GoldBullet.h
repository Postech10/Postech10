#ifndef GOLDBULLET_H
#define GOLDBULLET_H

#include "Bullet.h"

class GoldBullet: public Bullet{
public:
    GoldBullet();
    GoldBullet(int, int);
public slots:
    void move();
protected:
    int GoldPower;
};

#endif // GOLDBULLET_H
