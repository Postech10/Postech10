#include "fusion_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

fusion_button::fusion_button(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/fusion_button.png"));     //constructor
}

void fusion_button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->fuse_tower.size() == 2)
        qDebug()<<"Tower button was pressed!";
    else
        qDebug()<<"you need two towers to fusion.";
    game->fuse_mode = true;
}


