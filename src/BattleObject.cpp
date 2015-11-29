#include "BattleObject.h"
#include "Bullet.h"
#include "Game.h"
#define SCALE_FACTOR 300

extern Game* game;

BattleObject::BattleObject()
{
    Target = NULL;
    HasTarget = false;
    Hp = 0;                                    //?닿굔 媛쒕퀎?곸쑝濡??뺥빐?쇳븯誘濡??쇰떒 BattleObject?먯꽑 0
    AttackPower = 0;                            //?꾩? 媛숈??댁쑀
    DefensivePower = 0;                         //?꾩? 媛숈??댁쑀
    AttackSpeed = 0;
    Attackable = false;                         //?꾩? 媛숈??댁쑀
    timer = new QTimer();

    AttackRange = new QGraphicsEllipseItem(QRectF(0,0,SCALE_FACTOR,SCALE_FACTOR),this);
    AttackRange->setPen(QPen(Qt::DotLine));     //?먯꽑?쇰줈 踰붿쐞 蹂댁씠湲?

    QPointF poly_center(SCALE_FACTOR/2,SCALE_FACTOR/2);               //AttackRange??以묒떖
    poly_center = mapToScene(poly_center);
    QPointF object_center(x()+40, y()+50);       //?뺤떎??紐⑤쫫 ?섏쨷???붾쾭源낇븯硫댁꽌 留욎텧?앷컖
    QLineF ln(poly_center, object_center);
    AttackRange->setPos(x()+ln.dx(),y()+ln.dy());       //center 留욎텛湲?

    addSound("BulletWentOff","://sounds/BulletWentOff.wav");
}

BattleObject::~BattleObject()
{
    ;
}

void BattleObject::Attack()
{
    Bullet *bullet = new Bullet(AttackPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //constructor???덈뒗 object_center? ?숈씪 醫뚰몴
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //紐⑹쟻吏源뚯? ?좉툔湲?
    int angle = -1 * ln.angle();                    //object? target?ъ씠??媛곷룄瑜??ъ꽌
    bullet->setRotation(angle);                     //洹몃갑?μ쑝濡??좎븘媛?꾨줉 rotation???ㅼ젙
    game->scene->addItem(bullet);                   //異붽? .... ?닿굔 game?대씪??view媛 ?꾩젣?섏엳??寃쎌슦怨??섏쨷???ㅻⅨ 議곗썝???대뼸寃뚰븯?먯뿉 ?곕씪 ?щ씪吏덉삁??
}

double BattleObject::CalcDistance(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());       //嫄곕━ 援ы븯湲?
    return ln.length();
}

void BattleObject::IsHitBy(int AttackPower)
{
    Hp = Hp - AttackPower/DefensivePower;       //泥대젰 源롮씠??怨듭떇 ?異?.
}

int BattleObject::GetHp()
{
    return Hp;
}

int BattleObject::GetAttackPower()
{
    return AttackPower;
}

int BattleObject::GetDefensivePower()
{
    return DefensivePower;
}

int BattleObject::GetAttackSpeed()
{
    return AttackSpeed;
}

bool BattleObject::GetAttackable()
{
    return Attackable;
}

void BattleObject::SetHp(int Hp)
{
    this->Hp=Hp;
}

void BattleObject::SetAttackPower(int AttackPower)
{
    this->AttackPower=AttackPower;
}

void BattleObject::SetDefensivePower(int DefensivePower)
{
    this->DefensivePower=DefensivePower;
}

void BattleObject::SetAttackSpeed(int AttackSpeed)
{
    this->AttackSpeed=AttackSpeed;
}

void BattleObject::Activated(bool active)
{
    connect(timer,SIGNAL(timeout()),this,SLOT(SetTarget()));
    if(active){
        if(Attackable){
            timer->start(1000);
        }
    }
    else
        timer->stop();
}

void BattleObject::HideAttackRange()
{
    AttackRange->setPen(QPen(Qt::NoPen));     //?먯꽑?쇰줈 踰붿쐞 蹂댁씠湲?
}

void BattleObject::SetTarget()
{
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange? colliding?섎뒗 item??
    for(size_t j = 0, m = colliding_items.size();j<m;j++){              //遺?ろ엳???꾩씠?쒕뱾 ??寃??
        if(typeid(*(colliding_items[j]))==typeid(Enemy))                   //Enemy媛 ?덉쑝硫?
            break;                                                         //以묒??섍퀬 諛묒뿉 諛붾줈 ?ㅽ뻾
        else if(j == m-1){                                                 //?놁쑝硫?
            HasTarget = false;
            return;                                                        //由ы꽩
        }
    }
    double closest_dist = 300;              //泥섏쓬??踰붿쐞蹂대떎 ?곌컪?쇰줈 initialize
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test){                          //enemy??寃쎌슦留?
            double this_dist = CalcDistance(test);
            if(this_dist < closest_dist){               //?쒖씪 媛源뚯슫 enemy瑜?李얜뒗??(?섏쨷??怨듦꺽諛⑹떇諛붽씀怨??띠쓣???섏젙?덉젙)
                closest_dist = this_dist;
                Target = test;
                HasTarget = true;                  //媛?κ?源뚯슫 ?곸씠 Target???섎룄濡앺븿
            }
        }
    }
    if(HasTarget == true){
        Attack();                               //怨듦꺽
        playSound("BulletWentOff");
    }
}
