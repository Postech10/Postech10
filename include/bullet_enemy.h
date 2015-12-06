#ifndef BULLET_ENEMY
#define BULLET_ENEMY
#include "Bullet.h"
#include <QPixmap>

class Bullet_enemy : public Bullet{
public:
    Bullet_enemy(int power);
public slots:
    void move();
private:
    QPixmap* image;
};

#endif // BULLET_ENEMY

