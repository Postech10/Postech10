#ifndef BATTLEOBJECT
#define BATTLEOBJECT

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPointF>

class BattleObject: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BattleObject();
    void Attack();
    double CalcDistance(QGraphicsItem*);
    void IsHitBy(int);
    int GetHp();
public slots:
    void SetTarget();
protected:
    QGraphicsPolygonItem* AttackRange;
    QGraphicsItem* Target;
    bool HasTarget;
    int Hp;
    int DefensivePower;
    bool Attackable;
};

#endif // BATTLEOBJECT

