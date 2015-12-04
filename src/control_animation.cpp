#include "control_animation.h"
#include <Qtimer>

Control_Animation::Control_Animation()
{
    QTimer * main = new QTimer(this);
    connect(main,SIGNAL(timeout()),this,SLOT(Animate()));
    main->start(800);
    QTimer *sub = new QTimer(this);
    connect(sub, SIGNAL(timeout()), this, SLOT(Underattack()));
    sub->start(50);
}

void Control_Animation::ADD (AnimatedBattleObject* new_Animation)
{
    ObjectList.append(new_Animation);
}

void Control_Animation::Delete(AnimatedBattleObject* target)
{
    ObjectList.removeOne(target);
}

void Control_Animation::Animate ()
{
    for(int i=0; i < ObjectList.length(); i++)
    {
        ObjectList.at(i)->Animate();
    }
}

void Control_Animation::Underattack()
{
    for(int i=0; i < ObjectList.length(); i++)
    {
        if(ObjectList.at(i)->get_state() == UNDERATTACK)
            ObjectList.at(i)->Animate();
    }
}
