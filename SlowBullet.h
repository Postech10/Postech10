#ifndef SLOWBULLET_H
#define SLOWBULLET_H

#include "Bullet.h"

class SlowBullet: public Bullet
{
public:
    SlowBullet(int);           //constructor, int는 slowbullet의 느려지는 정도(?)을 뜻함
public slots:
    void move();        //slowbullet move method
protected:
    int SlowPower;
};

#endif // SLOWBULLET_H
