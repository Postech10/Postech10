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
    void upgrade(Upgrades, int);                    //이 method는 slow, gold가 적용되는 하위상속 tower에서는 overriding할 계획 일단 공격력, 방어력, 공속에 대해 구현함
    void fuseTower(Tower*, Tower*);                 //합성법 참고해서 만들기
    int GetTargetNum();
    int GetTowerCode();
protected:
    int TargetNum;
    int TowerCode;
};

#endif // TOWER

