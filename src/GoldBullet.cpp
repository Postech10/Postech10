#include "GoldBullet.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;


GoldBullet::GoldBullet()
{
    ;
}

GoldBullet::GoldBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SetAttackPower(attack);
    GoldPower = gold;
}

void GoldBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            if(dynamic_cast<Enemy*>(colliding_enemies[i])->DieOrNot())       //die?
                game->set_money(game->get_money()+GoldPower);                      //inc money
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
