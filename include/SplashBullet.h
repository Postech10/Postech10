#ifndef SPLASHBULLET_H
#define SPLASHBULLET_H

#include "Bullet.h"

#define SPLASH_SCALE_FACTOR 20

class SplashBullet: public Bullet{
public:
    SplashBullet(int);           //constructor, int means splashbullet's power
public slots:
    void move();        //splashbullet move method
};

#endif // SPLASHBULLET_H
