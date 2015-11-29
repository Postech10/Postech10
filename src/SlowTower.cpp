﻿#include "SlowTower.h"
#include "Game.h"

extern Game* game;

SlowTower::SlowTower()
{
    TargetNum = 1;
    TowerCode = SLOW;
    Hp = 100;
    SlowPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //珥덇린?ㅼ젙 ?섏쨷??諛몃윴?ㅻ? ?꾪빐 諛붽?嫄곗엫
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //?ъ쭊?ㅼ젙
}

void SlowTower::Attack()
{
    SlowBullet *bullet = new SlowBullet(SlowPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //constructor???덈뒗 object_center? ?숈씪 醫뚰몴
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //紐⑹쟻吏源뚯? ?좉툔湲?
    int angle = -1 * ln.angle();                    //object? target?ъ씠??媛곷룄瑜??ъ꽌
    bullet->setRotation(angle);                     //洹몃갑?μ쑝濡??좎븘媛?꾨줉 rotation???ㅼ젙
    game->scene->addItem(bullet);                   //異붽? .... ?닿굔 game?대씪??view媛 ?꾩젣?섏엳??寃쎌슦怨??섏쨷???ㅻⅨ 議곗썝???대뼸寃뚰븯?먯뿉 ?곕씪 ?щ씪吏덉삁??
}

void SlowTower::SetSlowPower(int slow)
{
    SlowPower = slow;
}

int SlowTower::GetSlowPower()
{
    return SlowPower;
}

