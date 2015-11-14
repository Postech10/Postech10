#include "MetalEngSenior.h"

MetalEngSenior::MetalEngSenior()
{
    TargetNum = 1;
    TowerCode = MES;
    Hp = 100;
    AttackPower = 40;
    DefensivePower = 20;
    GoldPower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    //나중에 알맞게 수정예정
}

void MetalEngSenior::Attack()
{
    IronBullet *bullet = new IronBullet(AttackPower, GoldPower);
    bullet->setPos(x()+50,y()+65);                  //constructor에 있는 object_center와 동일 좌표
    QLineF ln(QPointF(x()+50,y()+65),(Target->x(),Target->y()));      //목적지까지 선긋기
    int angle = -1 * ln.angle();                    //object와 target사이의 각도를 재서
    bullet->setRotation(angle);                     //그방향으로 날아가도록 rotation을 설정
    game->scene->addItem(bullet);                   //추가 .... 이건 game이라는 view가 전제되있을 경우고 나중에 다른 조원이 어떻게하냐에 따라 달라질예정
}

