#include "BuildTowerIcon.h"
#include "Game.h"

#include <qdebug.h>

extern Game *game;

BuildTowerIcon::BuildTowerIcon(char *filename,int _tower_code ,QGraphicsItem *parent){

    setPixmap(QPixmap(filename));     //constructor
    tower_code = _tower_code;
}
void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{   
    if(game->GetState() != Ingame){

        switch(tower_code){
        case NORMAL:
            if(game->get_money() >= 20){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),NORMAL);
                game->set_money(game->get_money()-20);
            }
            break;
        case SPLASH:
            if(game->get_money() >= 30){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),SPLASH);
                game->set_money(game->get_money()-30);
            }
            break;
        case SLOW:
            if(game->get_money() >= 30){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),SLOW);
                game->set_money(game->get_money()-30);
            }
            break;
        case POISON:
            if(game->get_money() >= 35){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),POISON);
                game->set_money(game->get_money()-35);
            }
            break;
        case CHAIN:
            if(game->get_money() >= 40){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),CHAIN);
                game->set_money(game->get_money()-40);
            }
            break;
        case GOLD:
            if(game->get_money() >= 60){
                game->SetAddMode(true);
                game->button_Pressed(event->pos(),GOLD);
                game->set_money(game->get_money()-60);
            }
            break;
        }
    }
}
