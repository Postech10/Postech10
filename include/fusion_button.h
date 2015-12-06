#ifndef FUSION_BUTTON_H
#define FUSION_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "soundobject.h"

class Fusion_Button: public SoundObject, public QGraphicsPixmapItem{
public:
    Fusion_Button(char* filename,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //?꾨? ??method
};

#endif // FUSION_BUTTON_H
