#include "enemycontrol.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

EnemyControl::EnemyControl(int level, QGraphicsScene* scene)
{
    ttt = scene;
    increaseLevel(level);

}

void EnemyControl::increaseLevel(int level)
{
    enemyNum=0;
    enemyLevel=level;
    qDebug() << "%d"<< enemyLevel;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));
    timer->start(5000-level*70);
}

void EnemyControl::spawn()
{
    qDebug() << "%d"<< enemyLevel;
    if (enemyNum<10){
       // if(enemyLevel>1)                 //?섏쨷???덈꺼 ?щ씪媛덈븣 ?꾩슂
         //   delete list[enemyNum];
        qDebug() << "%d"<< enemyLevel;
        if(enemyLevel%10==0)
            list[enemyNum]=new AttackableEnemy(enemyLevel);
        else
            list[enemyNum]=new Enemy(enemyLevel);

        ttt->addItem(list[enemyNum]);
        enemyNum=enemyNum+1;
    }
}
