#include "BuildTowerIcon.h"
#include "Game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(char *filename,int _tower_code ,QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
    tower_code = _tower_code;
}
void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->get_money() >= 20){
        game->SetAddMode(true);
        game->button_Pressed(event->pos(),tower_code);
        game->set_money(game->get_money()-20);
    }
}
