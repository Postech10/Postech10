#ifndef CONTROL_ANIMATION_H
#define CONTROL_ANIMATION_H

#include "AnimatedBattleObject.h"
#include <QObject>

class Control_Animation : public QObject
{
public:
    Control_Animation();
    void ADD(AnimatedBattleObject new_Object);
    void Animate();
    void Underattack();

protected:
    QVector <AnimatedBattleObject*> ObjectList;
};

#endif // CONTROL_ANIMATION_H
