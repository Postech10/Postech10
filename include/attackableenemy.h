#ifndef ATTACKABLEENEMY
#define ATTACKABLEENEMY
#include "enemy.h"
#include <QList>
#include <QPointF>

class Tower;

class AttackableEnemy : public Enemy{   //a kind of enemy with attacking skill
    Q_OBJECT    //for use of slot
public:
    AttackableEnemy(int level);     //constructor, initialization
    void Attack();                  //attack tower
    void property();                //give specific properties for each attackable enemy
    ~AttackableEnemy();             //destructor

public slots:
    void SetTarget();               //find tower inside the attackrange

private:
    QTimer* timer_search;           //for search target continuously
    Tower* targetTower;             //target tower to attack
    int search_clockrate;       //different clockrate according to enemy type


};

#endif // ATTACKABLEENEMY

