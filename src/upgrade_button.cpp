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
    if(game->waiting_line.size() == 1 && game->get_money() >= 15){
        Upgrades* up = new Upgrades();
        game->waiting_line[0]->upgrade(up,game->waiting_line[0]->GetTowerCode());
        game->set_money(game->get_money() - 15);
    }
    else
        qDebug()<<" you need only one tower to upgrade.";
}
