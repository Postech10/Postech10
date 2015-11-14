#include "GoldBullet.h"

GoldBullet::GoldBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/gold_bullet.png"));          //image 설정
    SetAttackPower(power);
    GoldPower = gold;
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //일정 시간마다 움직임
    move_timer->start(30);
}

void GoldBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            ((BattleObject *)colliding_enemies[i])->IsHitBy(AttackPower);
            if(((Enemy *)colliding_enemies[i])->DieOrNot())       //죽었는지 아닌지 확인필요.. 논의필요함
                game->money->inc(GoldPower);                      //이타워에 의해 죽었을때!! 돈 올라감
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
