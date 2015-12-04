#include "SlowBullet.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;

SlowBullet::SlowBullet()
{
    ;
}

SlowBullet::SlowBullet(int power)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SlowPower = power;
}

void SlowBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsSlowedBy(SlowPower);
            playSound("Hit");               //sound for hit
            game->scene->removeItem(this);
            QTimer::singleShot(3000,this,SLOT(callDestructor()));
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
