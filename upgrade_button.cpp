#include "upgrade_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

UpgradeButton::UpgradeButton(char *filename, QGraphicsItem *parent)
{
    setPixmap(QPixmap(filename));    //constructor
}
void UpgradeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    if(game->waiting_line.size() == 1)
        qDebug()<<" upgrade button was pressed!";
    else
        qDebug()<<" you need only one tower to upgrade.";
    game->upgrade_mode = true;
}
