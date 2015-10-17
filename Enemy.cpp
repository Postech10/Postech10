#include "Enemy.h"
#include <QTimer>
#include <qmath.h>
#include "Game.h"

extern Game *game;

Enemy::Enemy(QGraphicsItem *parent)                 //constructor
{
    setPixmap(QPixmap(":/images/enemy.png"));       //image
    points << QPointF(800,300); //이건 나중에 경로 복잡할때 이어서 붙이기<< QPointF(400,200);
    point_index = 0;            //초기 index
    dest = points[0];           //초기 dest
    setPos(0,300);
    rotateToPoint(dest);        //dest를 보고 move하기 위함
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move_forward()));     //일정 시간마다 move forward
    timer->start(150);

}

void Enemy::rotateToPoint(QPointF p)                //p를 향해 봄
{
    QLineF ln(pos(),p);                             //현재위치와 p를 이은 선
    setRotation(-1*ln.angle());                     //각도 설정해서 rotate
}

void Enemy::move_forward()                          //앞으로 전진
{
    QLineF ln(pos(),dest);                          //dest하고 현재위치 라인
    if(ln.length()<5){
        point_index++;                              //dest하고 가까워지면
        if(point_index >= points.size()){
            game->scene->removeItem(this);
            delete this;                            //point list끝났는지검사
            return;
        }
        dest=points[point_index];                   //다음 목적지로 이동
        rotateToPoint(dest);                        //향해 봐야함
    }
    int STEP_SIZE = 10;                              //가는 거리
    double theta = rotation();                      //현재 각도 알려줌

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));       //그 각도로 걷는다

    setPos(x()+dx,y()+dy);
}
