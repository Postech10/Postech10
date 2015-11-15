#include "Tower.h"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Bullet.h"
#include <QTimer>
#include "Game.h"
#include "Enemy.h"

extern Game *game;

Tower::Tower(): QObject()
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //사진설정

    QVector<QPointF> points;
    points << QPoint(1,0)<< QPoint(2,0)<< QPoint(3,1)<< QPoint(3,2)<< QPoint(2,3)
              << QPoint(1,3)<< QPoint(0,2)<< QPoint(0,1);
    int SCALE_FACTOR = 80;                          //범위 설정
    for (size_t i=0, n=points.size(); i<n;i++)
        points[i]*=SCALE_FACTOR;                    //확대

    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));     //점선으로 범위 보이기

    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;                //역시 확대
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+50, y()+65);
    QLineF ln(poly_center, tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());       //center 맞추기

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(2500);
    attack_dest = QPointF(800,0);

    choose = false;
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());       //거리 구하기
    return ln.length();
}

void Tower::fire()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+50,y()+65);
    QLineF ln(QPointF(x()+50,y()+65),attack_dest);      //목적지까지 선긋기
    int angle = -1 * ln.angle();                    //각도재서
    bullet->setRotation(angle);                     //rotation 설정
    game->scene->addItem(bullet);                   //추가
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(choose == false && game->GetAddMode()==false){
        if(game->waiting_line.size() < 2){
           attack_area->setPen(QPen(Qt::SolidLine));
           choose = true;
           game->waiting_line.push_back(this);
        }
    }

    else if(choose == true){
      attack_area->setPen(QPen(Qt::DotLine));
        choose = false;
        if(game->waiting_line[0] == this)
            game->waiting_line.remove(0);
        else
           game->waiting_line.remove(1);
    }        
}

void Tower::aquire_target()
{
    QList<QGraphicsItem *> colliding_items= attack_area->collidingItems();//attack_area와 colliding하는 item들
    if(colliding_items.size() <= 2){        //target아직 없음       //debug가 안되서 왜 2여야되는지 모름..나중에
        has_target = false;
        return ;
    }
    double closest_dist = 300;
    QPointF closest_pt = QPointF(0,0);
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if(enemy){
            double this_dist = distanceTo(enemy);
            if(this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt=colliding_items[i]->pos();
                has_target = true;                  //가장가까운 적을 closest_pt가 가리키게함
            }
        }
    }

    attack_dest = closest_pt;           //attack_dest설정
    fire();
}
