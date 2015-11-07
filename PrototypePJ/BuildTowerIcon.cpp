#include "BuildTowerIcon.h"
#include "Game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/add.png"));     //constructor
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!game->build){                   //NULL일때
        game->build = new Tower();      //build 새로운 타워 가리키는 포인터
        game->setCursor(QString(":/images/tower.png"));     //이미지 설정
    }
}