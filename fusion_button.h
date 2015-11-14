#ifndef FUSION_BUTTON_H
#define FUSION_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
class fusion_button: public QGraphicsPixmapItem{
public:
    fusion_button(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method
};

#endif // FUSION_BUTTON_H
