#ifndef TOWER
#define TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QColor>
#include "BattleObject.h"
//#include "Upgrades.h" //deleted because of MUTUAL INCLUSION


#define NORMAL 0
#define SPLASH 1
#define SLOW 2
#define POISON 3
#define CHAIN 4
#define GOLD 5
#define TUTOR 6
#define PROF 7
#define CES 8
#define JOBSBIO 9
#define MES 10
#define APPLE 11
#define JOBS 12
#define TRIPLE 13

class Tower: public BattleObject{
public:
    Tower();                                //constructor
    double distanceTo(QGraphicsItem *item); //item까지 거리
    void fire();                            //발사
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void aquire_target();                   //타겟결정
private:
    QGraphicsPolygonItem* attack_area;      //범위
    QPointF attack_dest;                    //목표
    bool has_target;                        //타겟 소유 여부
    bool choose;
};

#endif // TOWER

