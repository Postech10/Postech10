#ifndef CESBULLET_H
#define CESBULLET_H

#include "GoldBullet.h"

class CESBullet: public GoldBullet{
public:
    CESBullet(int,int);
public slots:
    void move();
};

#endif // CESBULLET_H
