#ifndef ANIMATION_H
#define ANIMATION_H
#include <QGraphicsPixmapItem>
#include <QString>
#include <QPixmap>
enum states { CALM, ATTACK, DESTROYED };

class AnimatedObject : public QGraphicsPixmapItem
{
public:
    Animation();
    Animation(QString filename);
    void Animate();
    void set_state(QString new_state);
    void set_image(QString new_image);
private:
    states state;
    QPixmap image;
    int state_cnt;
};

#endif // ANIMATION_H
