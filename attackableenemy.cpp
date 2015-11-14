#include "attackableenemy.h"
#include "bullet.h"
#include "QGraphicsScene"
#include <QTimer>
#include <QDebug>

AttackableEnemy::AttackableEnemy(int level):Enemy(level)
{
     qDebug() << "make attackable enemy";
    //battleobject------continue
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(attack()));
    timer->start(2000);

}


void AttackableEnemy::attack()
{
    Bullet* bullet = new Bullet();
    bullet->setPos(x()+this->rect().width()/2,y()+this->rect().height()/2);
    scene()->addItem(bullet);
}
