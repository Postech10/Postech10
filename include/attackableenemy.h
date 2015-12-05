#ifndef ATTACKABLEENEMY
#define ATTACKABLEENEMY
#include "enemy.h"
#include <QList>
#include <QPointF>
#include <QTimer>

class Tower;

class AttackableEnemy : public Enemy{
    Q_OBJECT
public:
    AttackableEnemy(int level);
    void Attack();
    void property();
    //void IsHitBy(int);

public slots:
    void SetTarget();\
private:
    QTimer* timer_search;
    Tower* targetTower;
    int search_clockrate;

};

#endif // ATTACKABLEENEMY

