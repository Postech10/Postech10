#include "bullet_enemy.h"
#include <QPixmap>
#include <QTimer>
#include <qmath.h>
#include "Game.h"
#include <QList>
#include <QGraphicsItem>
#include "Tower.h"
#include <QDebug>
#include <QPointF>
#define STEP 50

extern Game * game;

Bullet_enemy::Bullet_enemy(int power): Bullet(power){

    switch(power){
    case 10: setPixmap(QPixmap(":/images/Bullet_Normal.bmp"));break;
    case 20: setPixmap(QPixmap(":/images/Bullet_Normal.bmp"));break;
    case 30: setPixmap(QPixmap(":/images/Bullet_Normal.bmp"));break;
    case 40: setPixmap(QPixmap(":/images/Bullet_Normal.bmp"));break;
    }

    AttackPower=power;
    Activated(1);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));


}




void Bullet_enemy::move()
{
    QList<QGraphicsItem *> colliding_tower=this->collidingItems();      //bullet collides
    for(size_t i=0, n=colliding_tower.size();i<n;i++){
            Tower* tower=dynamic_cast<Tower *>(colliding_tower[i]);           //sound for hit
            if(tower){
                tower->IsHitBy(AttackPower);
                Activated(0);
                game->scene->removeItem(this);
                delete this;
                return;
            }
    }
    double theta = rotation();                      //set theta

    double dy = STEP*qSin(qDegreesToRadians(theta));
    double dx = STEP*qCos(qDegreesToRadians(theta));


    setPos(x()+dx,y()+dy);
}

