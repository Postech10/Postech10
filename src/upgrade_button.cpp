#include "upgrade_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

UpgradeButton::UpgradeButton(char *filename, QGraphicsItem *parent)
{
    setPixmap(QPixmap(filename));    //constructor

    //test upgrade sound binding---------------------------------------------
    //add a sound to this object-----------------------------FOR DEBUG-------
    addSound("upgrade", ":/sounds/upgrade.wav");//---------------------------
}
void UpgradeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    //just play when clicked-------------------------------------------------
    playSound("upgrade");//--------------------------------------------------
    if(game->waiting_line.size() == 1)
        qDebug()<<" upgrade button was pressed!";
    else
        qDebug()<<" you need only one tower to upgrade.";
    game->upgrade_mode = true;
}
