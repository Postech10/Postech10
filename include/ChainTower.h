#ifndef CHAINTOWER_H
#define CHAINTOWER_H

#include "Tower.h"
#include "Bullet.h"

class ChainTower: public Tower{
public:
    ChainTower();
public slots:
    void SetTarget();
};

#endif // CHAINTOWER_H
