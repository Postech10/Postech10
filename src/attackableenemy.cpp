#include "attackableenemy.h"
#include "Bullet.h"
#include "Tower.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QPointF>
#include <QList>
#include <QGraphicsItem>
#include "bullet_enemy.h"
#include "Game.h"

extern Game* game;
AttackableEnemy::AttackableEnemy(int level):Enemy(level)
{
    qDebug() << "make attackable enemy";
    DefensivePower=2;
    AttackPower=level;
    AttackSpeed=20;
    Attackable = true;


    timer_search = new QTimer();
    QObject::connect(timer_search, SIGNAL(timeout()), this, SLOT(SetTarget()));
    timer_search->start(1000);
    HasTarget = false;

}


void AttackableEnemy::Attack()
{
    Bullet_enemy* bbullet = new Bullet_enemy(AttackPower);
    bbullet->setPos(x()+30,y()+30);
    QLineF ln(QPointF(x()+30,y()+30), targetTower);
    int angle = -1 * ln.angle();
    bbullet->setRotation(angle);
    scene()->addItem(bbullet);
}
/*
void AttackableEnemy::IsHitBy(int power)
{
    Hp = Hp - power/DefensivePower;   //decrease Hp
    qDebug()<<Hp;


    if(Hp<=0){
        die();
        game->RenewEnemyNum(true);
        scene()->removeItem(hpBar);

        delete timer_search;
        delete timer;
        scene()->removeItem(this);


    }
    else
        cutHpbar();
}
*/

void AttackableEnemy::SetTarget()
{
    QList<QGraphicsItem *> colliding = AttackRange->collidingItems();
    HasTarget=false;

        if (colliding.size() == 1){
            HasTarget = false;
            return;
        }
        else if (colliding.size() > 1){
            double near_distance = 500;
            QPointF closest_item = QPointF(0,0);
            for (size_t i = 0, n = colliding.size(); i < n; i++){
                Tower* tower = dynamic_cast<Tower *>(colliding[i]);
                if (tower){


                    double distance = CalcDistance(tower);
                    if (distance < near_distance){
                        near_distance = distance;
                        closest_item = colliding[i]->pos();
                        HasTarget = true;

                    }
                }
            }
            if (HasTarget == true){
                targetTower = closest_item;
                Attack();
            }
        }
}

