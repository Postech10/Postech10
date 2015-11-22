#include "TripleMajorSenior.h"
#include "Game.h"

extern Game* game;

TripleMajorSenior::TripleMajorSenior()
{
    TargetNum = 1;
    TowerCode = TRIPLE;
    Hp = 100;
    AttackPower = 60;
    DefensivePower = 20;
    GoldPower = 30;
    AttackSpeed = 20;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //사진설정
}

void TripleMajorSenior::Attack()
{
    SplashPoisonBullet *bullet = new SplashPoisonBullet(AttackPower, GoldPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //constructor에 있는 object_center와 동일 좌표
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //목적지까지 선긋기
    int angle = -1 * ln.angle();                    //object와 target사이의 각도를 재서
    bullet->setRotation(angle);                     //그방향으로 날아가도록 rotation을 설정
    game->scene->addItem(bullet);                   //추가 .... 이건 game이라는 view가 전제되있을 경우고 나중에 다른 조원이 어떻게하냐에 따라 달라질예정

}

