#ifndef SPLASHLASER_H
#define SPLASHLASER_H

#include "GoldBullet.h"

class SplashLaser: public GoldBullet{
public:
    SplashLaser(int,int);
public slots:
    void move();
};

#endif // SPLASHLASER_H
