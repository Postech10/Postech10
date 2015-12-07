#include "control_animation.h"
#include <Qtimer>

Control_Animation::Control_Animation()
{
    QTimer * main = new QTimer(this); // timer to call Animate() regularly
    connect(main,SIGNAL(timeout()),this,SLOT(Animate()));
    main->start(800);
    QTimer *sub = new QTimer(this); // timer to call UnderAttack() regularly but currently not used.
    connect(sub, SIGNAL(timeout()), this, SLOT(Underattack()));
    sub->start(50);
}

void Control_Animation::ADD (AnimatedBattleObject* new_Animation) // add new object to list
{
    ObjectList.append(new_Animation);
}

void Control_Animation::Delete(AnimatedBattleObject* target) // delete target object from list
{
    ObjectList.removeOne(target);
}

void Control_Animation::Animate () // call Animate() for all obejct in the list
{
    for(int i=0; i < ObjectList.length(); i++)
    {
        ObjectList.at(i)->Animate();
    }
}

void Control_Animation::Underattack() // similar to Animate() but for the state UNDERATTACK. Currently not used.
{
    for(int i=0; i < ObjectList.length(); i++)
    {
        if(ObjectList.at(i)->get_state() == UNDERATTACK)
            ObjectList.at(i)->Animate();
    }
}
