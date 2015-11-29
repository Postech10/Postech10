#include "AnimatedBattleObject.h"
#include <QGraphicsPixmapItem>
#include <QColor>
#include <QBitmap>

AnimatedBattleObject::AnimatedBattleObject()
{
    image = new QPixmap();
    state_cnt = 1;
}

AnimatedBattleObject::AnimatedBattleObject(QString &filename)
{
    image = new QPixmap();
    *image = QPixmap(filename);
    image->setMask(image->createMaskFromColor(QColor(255, 0, 170)));
    QPixmap * copy = new QPixmap(image->copy(0, 0, 64 ,64));
    setPixmap(*copy);
    state_cnt = 1;
}

void AnimatedBattleObject::Animate()
{
    switch(this->state)
    {
        case CALM:
        {
            if(state_cnt)
            {
                QPixmap * copy = new QPixmap();
                *copy = this->image->copy(0, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 0;
            }
            else
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(64, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 1;
            }
            break;
        }
        case ATTACK:
        {
            if(state_cnt)
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(0, 128, 64, 64);
                setPixmap(*copy);
                state_cnt = 0;
            }
            else
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(64, 128, 64, 64);
                setPixmap(*copy);
                state_cnt = 1;
                set_state(CALM);
            }
            break;
        }
        case UNDERATTACK:
        {
            if(state_cnt == 0)
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(128, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 1;
                set_state(CALM);
            }
            if(state_cnt == 1)
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(64, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 2;
            }
            if(state_cnt == 2)
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(128, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 3;
            }
            if(state_cnt == 3)
            {
                QPixmap *copy = new QPixmap();
                *copy = this->image->copy(64, 0, 64, 64);
                setPixmap(*copy);
                state_cnt = 0;
            }
        }
    }
}

void AnimatedBattleObject::set_state(states new_state)
{
    state = new_state;
    state_cnt = 1;
    Animate();
    state_cnt = 1;
}

states AnimatedBattleObject::get_state()
{
    return this->state;
}

void AnimatedBattleObject::set_image(QString &new_image)
{
    image = new QPixmap(new_image);
    image->setMask(image->createMaskFromColor(QColor(255, 0, 170)));
    setPixmap(image->copy(0, 0, 64, 64));
}

QPixmap* AnimatedBattleObject::get_image()
{
    return image;
}
