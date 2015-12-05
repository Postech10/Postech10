#include "PMBullet.h"
#include <typeinfo>
#include <QBitmap>
#include "Game.h"

extern Game* game;

PMBullet::PMBullet(int attack, int slow)
{
    QPixmap image("://images/Bullet_PM.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    AttackPower = attack;
    SlowPower = slow;
}

void PMBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsSlowedBy(SlowPower);
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
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

