#ifndef FUSION_BUTTON_H
#define FUSION_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class Fusion_Button: public QGraphicsPixmapItem{
public:
    Fusion_Button(char* filename,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //?꾨? ??method
};

#endif // FUSION_BUTTON_H
