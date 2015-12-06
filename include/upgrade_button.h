#ifndef UPGRADE_BUTTON_H
#define UPGRADE_BUTTON_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <Upgrades.h>
#include "soundobject.h"

class UpgradeButton : public SoundObject, public QGraphicsPixmapItem{
private:
    Upgrades* up;

public:
    UpgradeButton(char* filename,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method

    Upgrades* getUp() {return up;}
};

#endif // UPGRADE_BUTTON_H
