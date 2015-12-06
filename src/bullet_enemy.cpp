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
#include <QBitmap>
#define STEP 30

extern Game * game;

Bullet_enemy::Bullet_enemy(int power): Bullet(power){
    switch(power){
    case 50: image = new QPixmap(":/images/Bullet_Normal.bmp");
        image->setMask(image->createMaskFromColor(QColor(255,0,170)));
        setPixmap(*image);break;
    case 100: image = new QPixmap(":/images/Bullet_Normal.bmp");
        image->setMask(image->createMaskFromColor(QColor(255,0,170)));
        setPixmap(*image);break;
    case 150: image = new QPixmap(":/images/Bullet_Punch.bmp");
        image->setMask(image->createMaskFromColor(QColor(255,0,170)));
        setPixmap(*image);break;
    case 200: image = new QPixmap(":/images/Bullet_Punch.bmp");
        image->setMask(image->createMaskFromColor(QColor(255,0,170)));
        setPixmap(*image);break;
    default:image = new QPixmap(":/images/Bullet_Punch.bmp");
        image->setMask(image->createMaskFromColor(QColor(255,0,170)));
        setPixmap(*image);break;
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
                tower->IsHitBy(AttackPower*2);
                Activated(0);
                game->scene->removeItem(this);
                delete image;
                delete this;
                return;
            }
    }
    double theta = rotation();                      //set theta

    double dy = STEP*qSin(qDegreesToRadians(theta));
    double dx = STEP*qCos(qDegreesToRadians(theta));


    setPos(x()+dx,y()+dy);
}

