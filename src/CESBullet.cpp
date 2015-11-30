#include "CESBullet.h"
#include "Game.h"

extern Game* game;


CESBullet::CESBullet(int attack,int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set pic
    SetAttackPower(attack);
    GoldPower = gold;
}

void CESBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //bullet collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsPoisonedBy(AttackPower);
            if(((Enemy *)colliding_enemies[i])->DieOrNot())         //die?
                game->set_money(game->get_money()+GoldPower);       //inc money
            playSound("Hit");               //sound for hit
            game->scene->removeItem(this);
            delete this;
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

