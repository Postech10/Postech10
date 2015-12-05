#include "PoisonBullet.h"
#include <typeinfo>
#include <QBitmap>
#include "Game.h"

extern Game* game;

PoisonBullet::PoisonBullet(int power)
{
    QPixmap image("://images/Bullet_Poison.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(power);
}

void PoisonBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsPoisonedBy(AttackPower);
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

