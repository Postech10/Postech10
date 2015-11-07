#ifndef TOWER
#define TOWER

#include "BattleObject.h"
#include "Upgrades.h"

#define NORMAL 0
#define SPLASH 1
#define SLOW 2
#define POISON 3
#define CHAIN 4
#define GOLD 5
#define TUTOR 6
#define PROF 7
#define CES 8
#define JOBSBIO 9
#define MES 10
#define APPLE 11
#define JOBS 12
#define TRIPLE 13

class Tower: public BattleObject{
    Q_OBJECT
public:
    Tower();
    void upgrade(Upgrade, int);
    void fuseTower(Tower*, Tower*);
protected:
    int TargetNum;
    int TowerCode;
};

#endif // TOWER

