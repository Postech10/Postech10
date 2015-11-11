#include "BuildTowerIcon.h"
#include "Game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(char *filename, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(filename));     //constructor
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->SetAddMode(true);
    game->button_Pressed();
}
