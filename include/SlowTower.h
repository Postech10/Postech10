#ifndef SLOWTOWER_H
#define SLOWTOWER_H

#include "Tower.h"
#include "SlowBullet.h"

class SlowTower: public Tower
{
public:
    SlowTower();
    void Attack();
    void SetSlowPower(int);
    int GetSlowPower();
protected:
    int SlowPower;
};

#endif // SLOWTOWER_H
