#include "bullet_enemy.h"
#include <qmath.h>
#include "Game.h"
#include <QList>
#include <QGraphicsItem>
#include "Tower.h"
#include <QPointF>
#include <QBitmap>
#define STEP 30  //bullet step size

extern Game * game;     //to access scene

Bullet_enemy::Bullet_enemy(int power): Bullet(power){       //different bullet image according to level
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
    QList<QGraphicsItem *> colliding_tower=this->collidingItems();      //bullet collides, get colliding item lists
    for(size_t i=0, n=colliding_tower.size();i<n;i++){
            Tower* tower=dynamic_cast<Tower *>(colliding_tower[i]);     //only tower item can be casted
            if(tower){      //if colliding item is tower
                tower->IsHitBy(AttackPower*2);      //hit the tower
                Activated(0);                       //stop to move
                game->scene->removeItem(this);
                delete image;
                delete this;
                return;
            }
    }
    double theta = rotation();                      //set theta

    double dy = STEP*qSin(qDegreesToRadians(theta));    //set x_step size, y_step size
    double dx = STEP*qCos(qDegreesToRadians(theta));


    setPos(x()+dx,y()+dy);      //move
}

