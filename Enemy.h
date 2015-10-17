#ifndef ENEMY
#define ENEMY

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList>
#include <QPointF>

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent=0);     //constructor
    void rotateToPoint(QPointF p);      //p를 향해 돈다
public slots:
    void move_forward();                //move method
private:
    QList<QPointF> points;              //member
    QPointF dest;
    int point_index;
};

#endif // ENEMY

