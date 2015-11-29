#ifndef SLOWBULLET_H
#define SLOWBULLET_H

#include "Bullet.h"

class SlowBullet: public Bullet
{
public:
    SlowBullet();
    SlowBullet(int);           //constructor, int??slowbullet???먮젮吏???뺣룄(?)???삵븿
public slots:
    void move();        //slowbullet move method
protected:
    int SlowPower;
};

#endif // SLOWBULLET_H
