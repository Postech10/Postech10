#ifndef ANIMATEDBATTLEOBJECT_H
#define ANIMATEDBATTLEOBJECT_H


#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>
#include <QColor>
#include <QBitmap>

enum states { CALM, ATTACK, UNDERATTACK };

class AnimatedBattleObject : public QGraphicsPixmapItem
{
public:
    AnimatedBattleObject();
    AnimatedBattleObject(QString &filename);
    void Animate();
    void set_state(states new_state);
    states get_state();
    void set_image(QString &new_image);
    QPixmap* get_image();

protected:
    states state;
    QPixmap *image;
    int state_cnt;
};

#endif // ANIMATEDBATTLEOBJECT_H
