#include "Bullet.h"
#include "BattleObject.h"

#define STEP_SIZE 30                            //기본 STEP Size.. 나중에바꿀예정

Bullet::Bullet(int power): QObject()
{
    setPixmap(QPixmap(":/images/bullet.png"));          //image 설정
    AttackPower = power;
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //일정 시간마다 움직임
    move_timer->start(30);
}
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            ((BattleObject *)colliding_enemies[i])->IsHitBy(AttackPower);
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
