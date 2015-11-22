#include "Bullet.h"
#include "Game.h"

extern Game* game;

Bullet::Bullet()
{
    ;
}

Bullet::Bullet(int power): QObject()
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image 설정
    SetAttackPower(power);
    move_timer = new QTimer();
}

void Bullet::SetAttackPower(int AttackPower)
{
    this->AttackPower = AttackPower;
}

int Bullet::GetAttackPower()
{
    return AttackPower;
}

void Bullet::Activated(bool active)
{
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //일정 시간마다 움직임
    if(active)
        move_timer->start(30);
    else
        move_timer->stop();
}
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            //please add isHitBy method and un-commentize this

            //game->scene->removeItem(colliding_enemies[i]);
            game->scene->removeItem(this);
            //game->SumWithEnemyNum(-1);
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta 설정

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
