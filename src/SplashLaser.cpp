#include "SplashLaser.h"
#include <typeinfo>
#include <QBitmap>
#include "Game.h"

extern Game* game;

SplashLaser::SplashLaser(int attack, int gold)
{
    QPixmap image("://images/Bullet_SplashLaser.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(attack);
    GoldPower = gold;
}

void SplashLaser::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Laser collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //if enemy
            QList<QGraphicsItem *> splashed_enemies= colliding_enemies[i]->collidingItems();     //item colliding with enemy that is hit by bullet
            for (size_t j=0, m=splashed_enemies.size();j<m;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy)){                          //if enemy
                    dynamic_cast<Enemy*>(splashed_enemies[j])->IsHitBy(AttackPower);
                    if(dynamic_cast<Enemy*>(colliding_enemies[j])->DieOrNot())              //die?
                        game->set_money(game->get_money()+GoldPower);                       //inc money
                }
            }
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

