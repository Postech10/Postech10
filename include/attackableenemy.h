#ifndef ATTACKABLEENEMY
#define ATTACKABLEENEMY
#include "enemy.h"

class AttackableEnemy : public Enemy{
    Q_OBJECT
public:
    AttackableEnemy(int level);
public slots:
    void attack();
};

#endif // ATTACKABLEENEMY

