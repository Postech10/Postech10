#include "AnimatedObject.h"
#include <QGraphicsPixmapItem>

AnimatedObject::Animation()
{
    state_cnt = 1;
}

AnimatedObject::Animation(QString filename)
{
    image = QPixmap(filename);
    setPixmap(image.copy(0, 0, 64, 64));
    state_cnt = 1;
}

void AnimatedObject::Animate()
{
    switch(this->state)
    {
    case CALM:
        if(state_cnt)
        {
            QPixmap copy = this->image.copy(0, 0, 64, 64);
            setPixmap(copy);
            state_cnt = 0;
        }
        else
        {
            QPixmap copy = this->image.copy(64, 0, 64, 64);
            setPixmap(copy);
            state_cnt = 1;
        }
        break;
    case ATTACK:
        if(state_cnt)
        {
            QPixmap copy = this->image.copy(0, 128, 64, 64);
            setPixmap(copy);
            state_cnt = 0;
        }
        else
        {
            QPixmap copy = this->image.copy(64, 128, 64, 64);
            setPixmap(copy);
            state_cnt = 1;
        }
        break;
    case DESTROYED:
        break;
    }
}

void AnimatedObject::set_state(states new_state)
{
    state = new_state;
}

void AnimatedObject::set_image(QString new_image)
{
    image = QPixmap(new_image);
    setPixmap(image.copy(0, 0, 64, 64));
}
