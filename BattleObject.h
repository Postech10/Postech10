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
    int GetAttackPower();
    int GetDefensivePower();
    int GetAttackSpeed();
    bool GetAttackable();
    void SetHp(int Hp);
    void SetAttackPower(int AttackPower);
    void SetDefensivePower(int DefensivePower);
    void SetAttackSpeed(int AttackSpeed);
public slots:
    void SetTarget();
protected:
    QGraphicsPolygonItem* AttackRange;
    QGraphicsItem* Target;
    bool HasTarget;
    int Hp;
    int AttackPower;
    int DefensivePower;
    int AttackSpeed;
    bool Attackable;
};

#endif // BATTLEOBJECT

