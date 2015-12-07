#ifndef BULLET_ENEMY
#define BULLET_ENEMY
#include "Bullet.h"
#include <QPixmap>

class Bullet_enemy : public Bullet{//bullet used by attackable enemy
public:
    Bullet_enemy(int power);//Constructor
public slots:
    void move();//move toward tower
private:
    QPixmap* image;//image of bullet
};

#endif // BULLET_ENEMY

