#include "CESBullet.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;


CESBullet::CESBullet(int attack,int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image ?ㅼ젙
    SetAttackPower(attack);
    GoldPower = gold;
}

void CESBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy??遺?ろ엳硫??щ씪吏?
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsPoisonedBy(AttackPower);  //enemy???쇱쓽 ?꾩슂
           // if(((Enemy *)colliding_enemies[i])->DieOrNot())       //二쎌뿀?붿? ?꾨땶吏 ?뺤씤?꾩슂.. ?쇱쓽?꾩슂??
              //  game->set_money(game->get_money()+GoldPower);                      //?댄??뚯뿉 ?섑빐 二쎌뿀?꾨븣!! ???щ씪媛?
            //please add method DieorNot, isPoisonedBy and un-commentize this.
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

