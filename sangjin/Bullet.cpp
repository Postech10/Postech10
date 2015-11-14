#include "Bullet.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include <QList>
#include "Game.h"
#include "Enemy.h"

extern Game *game;

Bullet::Bullet(): QObject()
{
    setPixmap(QPixmap(":/images/bullet.png"));          //image 설정
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //일정 시간마다 움직임
    move_timer->start(30);
}
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy랑 부딪히면 사라짐
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            game->scene->removeItem(colliding_enemies[i]);
            game->scene->removeItem(this);
            game->SumWithEnemyNum(-1);
            delete this;
            return;
        }
    }
    int STEP_SIZE = 30;                             //한번에 움직이는 정도
    double theta = rotation();                      //theta 설정

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
