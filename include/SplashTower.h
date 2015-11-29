#ifndef SPLASHTOWER_H
#define SPLASHTOWER_H

#include "Tower.h"
#include "SplashBullet.h"


class SplashTower: public Tower{
public:
    SplashTower();
    void Attack();
};

#endif // SPLASHTOWER_H
