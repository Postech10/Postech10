#include "control_animation.h"
#include <Qtimer>
Control_Animation::Control_Animation()
{
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Animate()));
    timer->start(800);
}

void Control_Animation::ADD (Animation new_Animation)
{
    ObjectList.append(new_Animation);
}

void Control_Animation::Animate ()
{
    for(int i=0; i < ObjectList.length(); i++)
    {
        ObjectList.at(i).Animate();
    }
}
