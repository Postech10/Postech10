#ifndef SPLASHPOISONBULLET_H
#define SPLASHPOISONBULLET_H

#include "GoldBullet.h"

class SplashPoisonBullet: public GoldBullet{
public:
    SplashPoisonBullet(int,int);
public slots:
    void move();
};

#endif // SPLASHPOISONBULLET_H
