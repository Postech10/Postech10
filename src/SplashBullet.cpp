#include "SplashBullet.h"
#include <typeinfo>
#include "Game.h"

#include <QThread>

extern Game* game;

SplashBullet::SplashBullet(int power)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SetAttackPower(power);
}

void SplashBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Bullet collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //if enemy
            QList<QGraphicsItem *> splashed_enemies= colliding_enemies[i]->collidingItems();     //all items in splash range
            for (size_t j=0, m=splashed_enemies.size();j<m;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy))                       //if enemy
                   dynamic_cast<Enemy*>(splashed_enemies[j])->IsHitBy(AttackPower);     //hit by
            }
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            playSound("Splash");               //sound for splash
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


