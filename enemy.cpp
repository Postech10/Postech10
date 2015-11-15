#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>

#define width 500
#define height 500

Enemy::Enemy(int level)
{
    qDebug() << "make enemy";
    path[0][0]=70*width/100;           //path represented by points 0->1.....
    path[0][1]=80*height/100;
    path[1][0]=45*width/100;
    path[1][1]=80*height/100;
    path[2][0]=20*width/100;
    path[2][1]=80*height/100;
    path[3][0]=20*width/100;
    path[3][1]=60*height/100;
    path[4][0]=50*width/100;
    path[4][1]=60*height/100;
    path[5][0]=80*width/100;
    path[5][1]=60*height/100;
    path[6][0]=80*width/100;
    path[6][1]=35*height/100;
    path[7][0]=80*width/100;
    path[7][1]=10*height/100;
    path[8][0]=45*width/100;
    path[8][1]=10*height/100;
    path[9][0]=20*width/100;
    path[9][1]=10*height/100;

    currentPath=-1;     //not yet on path

    clockRate=10000/(60+level);   //different velocity according to level

    setRect(0,0,width/10,height/10);
    setPos(path[0][0],path[0][1]);

    //move according to signal
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(clockRate);
}

void Enemy::move()
{
    if ((x()== path[currentPath+1][0]) && (y()==path[currentPath+1][1])){
        currentPath++;
        x_move=(path[currentPath+1][0]-path[currentPath][0])/50;
        y_move=(path[currentPath+1][1]-path[currentPath][1])/50;
    }

    setPos(x()+x_move, y()+y_move);

    if((x()== path[9][0]) && (y()==path[9][1])){
        qDebug() << "Fail to remove enemy";
        scene()->removeItem(this);
        delete this;
    }

}
