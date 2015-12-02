#ifndef BULLET_ENEMY
#define BULLET_ENEMY
#include "Bullet.h"

class Bullet_enemy : public Bullet{
public:
    Bullet_enemy(int power);
public slots:
    void move();
};

#endif // BULLET_ENEMY

