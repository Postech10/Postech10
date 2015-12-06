#include "button.h"
#include "Game.h"

extern Game *game;

Button::Button(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    game->scene->removeItem(this);
    QTimer::singleShot(500,game,SLOT(change()));
    game->button_Pressed(event->pos(),0);
}


