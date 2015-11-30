#ifndef SLOWBULLET_H
#define SLOWBULLET_H

#include "Bullet.h"

class SlowBullet: public Bullet
{
public:
    SlowBullet();
    SlowBullet(int);           //constructor, int means slowbullet's slow power
public slots:
    void move();        //slowbullet move method
protected:
    int SlowPower;
};

#endif // SLOWBULLET_H
