#ifndef SPLASHPOISONBULLET_H
#define SPLASHPOISONBULLET_H

#include "GoldBullet.h"

#define SPLASH_SCALE_FACTOR 20

class SplashPoisonBullet: public GoldBullet{
public:
    SplashPoisonBullet(int,int);
public slots:
    void move();
};

#endif // SPLASHPOISONBULLET_H
