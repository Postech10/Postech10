#include "fusion_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

Fusion_Button::Fusion_Button(char *filename, QGraphicsItem *parent){
    setPixmap(QPixmap(filename));     //constructor
    addSound("Combine", "resources/sounds/fusion.wav");
    addSound("Fail", "resources/sounds/unablebutton.wav");
}
void Fusion_Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    bool isFuseSuccess;
    game->scene->removeItem(this);
    game->SetFuseMode(true);
    QTimer::singleShot(150,game,SLOT(change()));
    isFuseSuccess = game->FuseTower();
    if(isFuseSuccess) playSound("Combine");
    else playSound("Fail");
}


