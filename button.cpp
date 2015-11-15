#include "Button.h"
#include "Game.h"

extern Game *game;

Button::Button(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->button_Pressed(event->pos());
}


