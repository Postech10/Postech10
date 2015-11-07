#include "BuildTowerIcon.h"
#include "Game.h"

extern Game *game;

BuildTowerIcon::BuildTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/add.png"));     //constructor
}

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    game->build.push_back(new Tower());      //build 새로운 타워 가리키는 포인터
    game->setCursor(QString(":/images/Mechanical.psd"));     //이미지 설정
    game->add_mode = true;

}
