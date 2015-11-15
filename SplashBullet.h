#ifndef SPLASHBULLET_H
#define SPLASHBULLET_H

#include "Bullet.h"

#define SPLASH_SCALE_FACTOR 20

class SplashBullet: public Bullet{
public:
    SplashBullet(int);           //constructor, int는 splashbullet의 파괴력을 뜻함
public slots:
    void move();        //splashbullet move method
};

#endif // SPLASHBULLET_H