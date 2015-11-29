#ifndef GOLDTOWER_H
#define GOLDTOWER_H

#include "Tower.h"
#include "GoldBullet.h"

class GoldTower: public Tower{
public:
    GoldTower();
    void Attack();
    void SetGoldPower(int);
    int GetGoldPower();
protected:
    int GoldPower;
};

#endif // GOLDTOWER_H
