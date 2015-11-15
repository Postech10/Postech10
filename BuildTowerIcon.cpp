#include "BuildTowerIcon.h"
#include "Game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
}
void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->get_money() >= 20){
        game->SetAddMode(true);
        game->button_Pressed(event->pos());
        game->set_money(game->get_money()-20);
    }
}
