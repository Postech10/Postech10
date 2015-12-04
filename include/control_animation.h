#ifndef CONTROL_ANIMATION_H
#define CONTROL_ANIMATION_H

#include "AnimatedBattleObject.h"
#include <QObject>

class Control_Animation : public QObject
{
    Q_OBJECT

public:
    Control_Animation();
    void ADD(AnimatedBattleObject* new_Object);
    void Delete(AnimatedBattleObject* target);

public slots:
    void Animate();
    void Underattack();

protected:
    QVector <AnimatedBattleObject*> ObjectList;
};

#endif // CONTROL_ANIMATION_H
