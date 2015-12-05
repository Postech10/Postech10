#ifndef BATTLEOBJECT
#define BATTLEOBJECT


#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPointF>
#include <QTimer>
#include <QPen>
#include "soundobject.h"
#include "animatedbattleobject.h"

class BattleObject: public QObject, public AnimatedBattleObject, public SoundObject{
    Q_OBJECT
public:
    BattleObject();
    virtual ~BattleObject();
    virtual void Attack();
    double CalcDistance(QGraphicsItem*);
    virtual void IsHitBy(int);
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
    void HideAttackRange();
    void setHpbar();
    void cutHpbar();
    inline void DelHpBar(){delete hpBar;}
public slots:
    virtual void SetTarget();
protected:
    QGraphicsEllipseItem* AttackRange;
    QGraphicsItem* Target;
    bool HasTarget;
    int Hp;
    int AttackPower;
    int DefensivePower;
    int AttackSpeed;
    bool Attackable;
    QTimer* timer;
    int Full;    //new
    int slowLevel;
    QGraphicsRectItem* hpBar;   //new
};

#endif // BATTLEOBJECT

