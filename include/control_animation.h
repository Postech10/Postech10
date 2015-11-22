#ifndef CONTROL_ANIMATION_H
#define CONTROL_ANIMATION_H
#include "Animation.h"

class Control_Animation
{
public:
    Control_Animation();
    void ADD();\
    void Animate();

private:
    QVector <Animation> ObjectList;
};

#endif // CONTROL_ANIMATION_H
