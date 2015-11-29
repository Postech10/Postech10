#include "PMBullet.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;

PMBullet::PMBullet(int attack, int slow)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image ?ㅼ젙
    AttackPower = attack;
    SlowPower = slow;
}

void PMBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy??遺?ろ엳硫??щ씪吏?
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            //dynamic_cast<Enemy*>(colliding_enemies[i])->IsSlowedBy(SlowPower);  //enemy???쇱쓽 ?꾩슂
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            //please add isSlowedBy and un-commentize this.
            playSound("Hit");               //?곸쨷 ???섎뒗 ?뚮━
            game->scene->removeItem(this);                      //瑗?븘?뷀븳吏 紐⑤Ⅴ寃좎쓬.. ?섏쨷???섏젙?덉젙
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta ?ㅼ젙

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

