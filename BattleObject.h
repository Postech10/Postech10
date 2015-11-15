#ifndef BATTLEOBJECT
#define BATTLEOBJECT

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QObject>
#include <QPointF>
#include <QTimer>

class BattleObject: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    BattleObject();
    virtual void Attack();
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
    virtual void Activated(bool);
public slots:
    virtual void SetTarget();
protected:
    QGraphicsPolygonItem* AttackRange;
    QGraphicsItem* Target;
    bool HasTarget;
    int Hp;
    int AttackPower;
    int DefensivePower;
    int AttackSpeed;
    bool Attackable;
    QTimer* timer;
};

#endif // BATTLEOBJECT

