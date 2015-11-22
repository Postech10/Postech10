#include "Attackableenemy.h"
#include "bullet.h"
#include "QGraphicsScene"
#include <QTimer>
#include <QDebug>

AttackableEnemy::AttackableEnemy(int level):Enemy(level)
{
    qDebug() << "make attackable enemy";
    DefensivePower=20;
    AttackPower=100*level/10;
    AttackSpeed=10;
    Attackable = true;


    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(attack()));
    timer->start(2000);

}


void AttackableEnemy::attack()
{
    Bullet* bullet = new Bullet();
    bullet->setPos(x(),y());
    scene()->addItem(bullet);
}
