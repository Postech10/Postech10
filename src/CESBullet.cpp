#include "CESBullet.h"
#include "Game.h"
#include <QBitmap>

extern Game* game;


CESBullet::CESBullet(int attack,int gold)
{
    QPixmap image("://images/Bullet_CES.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
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
            QTimer::singleShot(3000,this,SLOT(callDestructor()));
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

