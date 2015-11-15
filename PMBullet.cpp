#include "PMBullet.h"

PMBullet::PMBullet(int attack, int slow)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image 설정
    AttackPower = attack;
    SlowPower = slow;
}

void PMBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsSlowedBy(SlowPower);  //enemy에 논의 필요
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            game->scene->removeItem(this);                      //꼭필요한지 모르겠음.. 나중에 수정예정
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta 설정

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

