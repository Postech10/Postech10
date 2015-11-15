#include "GoldBullet.h"


GoldBullet::GoldBullet()
{
    ;
}

GoldBullet::GoldBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/gold_bullet.png"));          //image 설정
    SetAttackPower(power);
    GoldPower = gold;
}

void GoldBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            if(dynamic_cast<Enemy*>(colliding_enemies[i])->DieOrNot())       //죽었는지 아닌지 확인필요.. 논의필요함
                game->set_money(game->get_money()+GoldPower);                      //이타워에 의해 죽었을때!! 돈 올라감
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
