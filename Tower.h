#ifndef TOWER
#define TOWER

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>

class Tower: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower();                                //constructor
    double distanceTo(QGraphicsItem *item); //item까지 거리
    void fire();                            //발사
public slots:
    void aquire_target();                   //타겟결정
private:
    QGraphicsPolygonItem* attack_area;      //범위
    QPointF attack_dest;                    //목표
    bool has_target;                        //타겟 소유 여부
};

#endif // TOWER

