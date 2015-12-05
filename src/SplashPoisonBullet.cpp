#include "SplashPoisonBullet.h"
#include <typeinfo>
#include <QBitmap>
#include "Game.h"

extern Game* game;

SplashPoisonBullet::SplashPoisonBullet(int attack, int gold)
{
    QPixmap image("://images/Bullet_SplashPoison.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(attack);
    GoldPower = gold;
}

void SplashPoisonBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //SplashPoisonBullet collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if((typeid(*(colliding_enemies[i]))==typeid(Enemy))||typeid(*(colliding_enemies[i]))==typeid(AttackableEnemy)){         //if enemy
            QList<QGraphicsItem *> splashed_enemies= colliding_enemies[i]->collidingItems();     //item colliding with enemy that is hit by bullet
            for (size_t j=0, m=splashed_enemies.size();j<m;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy)){
                    dynamic_cast<Enemy*>(splashed_enemies[j])->IsGoldPoisonedBy(AttackPower,GoldPower); //poisoned related money.... should be discussed
                }
                else if(typeid(*(splashed_enemies[j]))==typeid(AttackableEnemy)){
                    dynamic_cast<AttackableEnemy*>(splashed_enemies[j])->IsGoldPoisonedBy(AttackPower,GoldPower);
                }
            }
            if(typeid(*(colliding_enemies[i]))==typeid(Enemy))
                dynamic_cast<Enemy*>(colliding_enemies[i])->IsGoldPoisonedBy(AttackPower,GoldPower);
            else if(typeid(*(colliding_enemies[i]))==typeid(AttackableEnemy))
                dynamic_cast<AttackableEnemy*>(colliding_enemies[i])->IsGoldPoisonedBy(AttackPower,GoldPower);
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

