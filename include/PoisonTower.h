#ifndef POISONTOWER_H
#define POISONTOWER_H

#include "Tower.h"
#include "PoisonBullet.h"

class PoisonTower: public Tower{
public:
    PoisonTower();
    void Attack();
};

#endif // POISONTOWER_H
