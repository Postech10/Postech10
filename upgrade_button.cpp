#include "upgrade_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

UpgradeButton::UpgradeButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

         setPixmap(QPixmap(":/images/upgrade_button.png"));     //constructor
}

void UpgradeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    if(game->fuse_tower.size() == 1)
        qDebug()<<"upgrade button was pressed!";
    else
        qDebug()<<"you need only one tower to upgrade.";
    game->fuse_mode = true;
}
