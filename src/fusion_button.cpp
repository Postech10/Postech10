#include "fusion_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

Fusion_Button::Fusion_Button(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
}
void Fusion_Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->waiting_line.size() == 2)
        qDebug()<<" Fusion button was pressed!";
    else
        qDebug()<<" you need two towers to fusion.";
    game->fuse_mode = true;
}


