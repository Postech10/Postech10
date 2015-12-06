
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
     Hp=500*level;
     DefensivePower=2;
     AttackPower=level*5;
     AttackSpeed=20;
     Attackable = true;
     search_clockrate=1000;

    property();

    timer_search = new QTimer();
    QObject::connect(timer_search, SIGNAL(timeout()), this, SLOT(SetTarget()));
    timer_search->start(search_clockrate);
    HasTarget = false;

}


void AttackableEnemy::Attack()
{
    Bullet_enemy* bbullet = new Bullet_enemy(AttackPower);
    bbullet->setPos(x()+30,y()+30);
    QLineF ln(QPointF(x()+30,y()+30), QPointF(targetTower->x()+30, targetTower->y()+30));
    int angle = -1 * ln.angle();
    bbullet->setRotation(angle);
    scene()->addItem(bbullet);
}

void AttackableEnemy::property()
{
    switch(getLevel()){
    case 10: break;
    case 20: setClockRate(5); break;
    case 30: AttackPower=5000; search_clockrate=20000; setClockRate(20); break;//다 죽임
    case 40: AttackPower=5000; search_clockrate=5000; setClockRate(5); break;//범위 넓힘
    case 41: AttackPower=5000; search_clockrate=500; setClockRate(5); break;
    }
}

AttackableEnemy::~AttackableEnemy()
{
    if(timer_search)
        delete timer_search;

}


void AttackableEnemy::SetTarget()
{
    if(DieOrNot()==0){
    QList<QGraphicsItem *> colliding = AttackRange->collidingItems();
    HasTarget=false;

        if (colliding.size() == 1){
            HasTarget = false;
            return;
        }
        else if (colliding.size() > 1){
            double near_distance = 500;
            for (size_t i = 0, n = colliding.size(); i < n; i++){
                Tower* tower = dynamic_cast<Tower *>(colliding[i]);
                if (tower){
                    double distance = CalcDistance(tower);
                    if (distance < near_distance){
                        near_distance = distance;
                        targetTower=tower;
                        HasTarget = true;
                    }
                }
            }
            if (HasTarget == true){
                Attack();
            }
        }
    }
    else
        delete timer_search;
}

