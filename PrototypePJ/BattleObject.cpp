
#include "BattleObject.h"

#define SCALE_FACTOR 80

BattleObject::BattleObject()
{
    setPixmap(QPixmap(":/images/BattleObject.png"));     //사진설정

    QVector<QPointF> points;                             //AttackRange 설정 과정
    points << QPoint(1,0)<< QPoint(2,0)<< QPoint(3,1)<< QPoint(3,2)<< QPoint(2,3)
              << QPoint(1,3)<< QPoint(0,2)<< QPoint(0,1);//범위 설정 -> 나중에 원으로 하는법 알아내면 바꿀예정 지금은 8각형임..
    for (size_t i=0, n=points.size(); i<n;i++)
        points[i]*=SCALE_FACTOR;                    //확대

    AttackRange = new QGraphicsPolygonItem(QPolygonF(points),this);
    AttackRange->setPen(QPen(Qt::DotLine));     //점선으로 범위 보이기

    QPointF poly_center(1.5,1.5);               //AttackRange의 중심
    poly_center *= SCALE_FACTOR;                //역시 확대
    poly_center = mapToScene(poly_center);
    QPointF object_center(x()+50, y()+65);       //확실히 모름 나중에 디버깅하면서 맞출생각
    QLineF ln(poly_center, object_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());       //center 맞추기

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(SetTarget()));
    timer->start(1/AttackSpeed);                         //나중에 알맞게 수정예정

    Target = NULL;
    HasTarget = false;
    Hp = 0;                                    //이건 개별적으로 정해야하므로 일단 BattleObject에선 0
    AttackPower = 0;                            //위와 같은이유
    DefensivePower = 0;                         //위와 같은이유
    AttackSpeed = 0;
    Attackable = false;                         //위와 같은이유
}

void BattleObject::Attack()
{
    Bullet *bullet = new Bullet(AttackPower);
    bullet->setPos(x()+50,y()+65);                  //constructor에 있는 object_center와 동일 좌표
    QLineF ln(QPointF(x()+50,y()+65),(Target->x(),Target->y()));      //목적지까지 선긋기
    int angle = -1 * ln.angle();                    //object와 target사이의 각도를 재서
    bullet->setRotation(angle);                     //그방향으로 날아가도록 rotation을 설정
    game->scene->addItem(bullet);                   //추가 .... 이건 game이라는 view가 전제되있을 경우고 나중에 다른 조원이 어떻게하냐에 따라 달라질예정
}

double BattleObject::CalcDistance(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());       //거리 구하기
    return ln.length();
}

void BattleObject::IsHitBy(int AttackPower)
{
    Hp = Hp - AttackPower/DefensivePower;       //체력 깎이는 공식 대충..
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

void BattleObject::SetTarget()
{
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange와 colliding하는 item들
    if(colliding_items.size() <= 2){        //target아직 없음       //debug가 안되서 왜 2여야되는지 모름..나중에
        has_target = false;
        return ;
    }
    double closest_dist = 300;              //처음엔 범위보다 큰값으로 initialize
    QPointF closest_pt = QPointF(0,0);      //가장 가까운 아이템의 좌표
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test){                          //enemy일 경우만
            double this_dist = CalcDistance(test);
            if(this_dist < closest_dist){               //제일 가까운 enemy를 찾는다 (나중에 공격방식바꾸고 싶을때 수정예정)
                closest_dist = this_dist;
                Target = test;
                has_target = true;                  //가장가까운 적이 Target이 되도록함
            }
        }
    }

    Attack();                               //공
}
