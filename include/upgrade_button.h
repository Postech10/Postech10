#ifndef UPGRADE_BUTTON_H
#define UPGRADE_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <Upgrades.h>

class UpgradeButton : public QGraphicsPixmapItem{
public:
    UpgradeButton(char* filename,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //?꾨? ??method
};

#endif // UPGRADE_BUTTON_H
