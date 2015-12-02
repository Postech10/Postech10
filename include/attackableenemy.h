#ifndef ATTACKABLEENEMY
#define ATTACKABLEENEMY
#include "enemy.h"
#include <QList>
#include <QPointF>
#include <QTimer>

class AttackableEnemy : public Enemy{
    Q_OBJECT
public:
    AttackableEnemy(int level);
    void Attack();
    //void IsHitBy(int);

public slots:
    void SetTarget();\
private:
    QTimer* timer_search;
    QPointF targetTower;

};

#endif // ATTACKABLEENEMY

