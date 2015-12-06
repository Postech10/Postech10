#include "button.h"
#include "Game.h"
#include "titleandintro.h"
#include <qdebug.h>

extern Game *game;
extern TitleAndIntro* title;
Button::Button(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(title->page_num <10) title->button_Pressed(event->scenePos());
    else game->button_Pressed(event->pos(),0);
}
