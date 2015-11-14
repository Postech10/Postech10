#ifndef UPGRADE_BUTTON_H
#define UPGRADE_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
class UpgradeButton : public QGraphicsPixmapItem{
public:
    UpgradeButton(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method
};

#endif // UPGRADE_BUTTON_H
