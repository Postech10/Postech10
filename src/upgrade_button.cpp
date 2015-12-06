#include "upgrade_button.h"
#include "Game.h"
#include <QDebug>
extern Game *game;

UpgradeButton::UpgradeButton(char *filename, QGraphicsItem *parent)
{
    setPixmap(QPixmap(filename));    //constructor
    up = new Upgrades();
    addSound("Upgrade", "resources/sounds/upgrade.wav");
    addSound("Fail", "resources/sounds/unablebutton.wav");
}
void UpgradeButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    game->scene->removeItem(this);
    game->SetUpgradeMode(true);
    QTimer::singleShot(150,game,SLOT(change()));

    if(game->waiting_line.size() == 1 && game->get_money()>= 15){
        playSound("Upgrade");
        game->waiting_line[0]->upgrade(up,game->waiting_line[0]->GetTowerCode());
        game->set_money(game->get_money() - 15);
        game->SetUpgradeMode(true);
    }
    else
        playSound("Fail");
        qDebug()<<" you need only one tower to upgrade.";
}

