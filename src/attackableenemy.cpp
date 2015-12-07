#include "attackableenemy.h"
#include "Bullet.h"
#include "Tower.h"
#include <QGraphicsScene>
#include <QVector>
#include <QPointF>
#include <QGraphicsItem>
#include "bullet_enemy.h"
#include "Game.h"

extern Game* game;
AttackableEnemy::AttackableEnemy(int level):Enemy(level)
{
     Hp=200*level;      //initialization, stronger than normal enemies
     DefensivePower=3;
     AttackPower=level*5;
     AttackSpeed=20;
     Attackable = true;
     search_clockrate=2000;

    property();     //give specific properties to each enemy

    timer_search = new QTimer();
    QObject::connect(timer_search, SIGNAL(timeout()), this, SLOT(SetTarget()));     //timer connection, set target at every timeout
    timer_search->start(search_clockrate);      //start target searching(tower)
    HasTarget = false;      //first, no target

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

void AttackableEnemy::property()        //give specific properties!!
{
    switch(getLevel()){
    case 10: break;
    case 20: setClockRate(5); break;        //fast
    case 30: AttackPower=5000; search_clockrate=20000; setClockRate(20); break;     //remove tower
    case 40: AttackPower=5000; search_clockrate=5000; setClockRate(5); break;       //fast + remove tower
    case 41: AttackPower=5000; search_clockrate=500; setClockRate(5); break;        //fast + remove tower more frequently
    }
}

AttackableEnemy::~AttackableEnemy()
{
    if(timer_search!=nullptr)         //delete pointer
        delete timer_search;

}


void AttackableEnemy::SetTarget()
{
    if(DieOrNot()==0){      //only when enemy is alive
    QList<QGraphicsItem *> colliding = AttackRange->collidingItems();   //get item lists inside the attack range
    HasTarget=false;

        if (colliding.size() == 1){     //only itself inside the range
            HasTarget = false;
            return;
        }
        else if (colliding.size() > 1){     //something, non-itself exists inside the range
            double near_distance = 500;
            for (size_t i = 0, n = colliding.size(); i < n; i++){
                Tower* tower = dynamic_cast<Tower *>(colliding[i]);     //find tower in the lists
                if (tower){
                    double distance = CalcDistance(tower);
                    if (distance < near_distance){      //find the nearst tower
                        near_distance = distance;
                        targetTower=tower;
                        HasTarget = true;       //target exists
                    }
                }
            }
            if (HasTarget == true){     //if target exists, attack the tower
                Attack();
            }
        }
    }
    else{       //if dead, stop searching and get money
        delete timer_search;
        timer_search=nullptr;
        game->set_money(game->get_money()+getLevel()*10);
    }
}

