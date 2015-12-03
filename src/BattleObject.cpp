#include "BattleObject.h"
#include "Bullet.h"
#include "Game.h"
#define SCALE_FACTOR 300
#define width 600
#define height 600

extern Game* game;

BattleObject::BattleObject()
{
    Target = NULL;
    HasTarget = false;
    Hp = 0;
    AttackPower = 0;
    DefensivePower = 0;
    AttackSpeed = 0;
    Attackable = false;                         //these informations will be changed for balance
    timer = new QTimer();

    AttackRange = new QGraphicsEllipseItem(QRectF(0,0,SCALE_FACTOR,SCALE_FACTOR),this);
    AttackRange->setPen(QPen(Qt::DotLine));     //range dotline

    QPointF poly_center(SCALE_FACTOR/2,SCALE_FACTOR/2);               //center of AttackRange
    poly_center = mapToScene(poly_center);
    QPointF object_center(x()+40, y()+50);       //depend on image file
    QLineF ln(poly_center, object_center);
    AttackRange->setPos(x()+ln.dx(),y()+ln.dy());       //sync center

    addSound("BulletWentOff","resources/sounds/BulletWentOff.wav");
}

BattleObject::~BattleObject()
{
    ;
}

void BattleObject::Attack()
{
    Bullet *bullet = new Bullet(AttackPower);
    bullet->Activated(true);
    bullet->setPos(x()+40,y()+50);                  //same position with object_center(in constructor)
    QLineF ln(QPointF(x()+40,y()+50),QPointF(Target->x(),Target->y()));      //line to target
    int angle = -1 * ln.angle();                    //angle between object and target
    bullet->setRotation(angle);                     //set rotation
    game->scene->addItem(bullet);                   //add it in game scene
}

double BattleObject::CalcDistance(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());       //calc distance
    return ln.length();
}

void BattleObject::IsHitBy(int AttackPower)
{
    Hp = Hp - AttackPower/DefensivePower;       //not perfect equation yet
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
    AttackRange->setPen(QPen(Qt::NoPen));     //hide dot line
}

void BattleObject::SetTarget()
{
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange's colliding item
    for(size_t j = 0, m = colliding_items.size();j<m;j++){
        if(typeid(*(colliding_items[j]))==typeid(Enemy))                   //if Enemy
            break;
        else if(j == m-1){                                                 //no Enemy
            HasTarget = false;
            return;                                                        //return
        }
    }
    double closest_dist = 300;              //first initialize longer than range
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test){                          //only for enemy
            double this_dist = CalcDistance(test);
            if(this_dist < closest_dist){               //find closest enemy
                closest_dist = this_dist;
                Target = test;
                HasTarget = true;                  //the closest enemy is target
            }
        }
    }
    if(HasTarget == true){
        Attack();                               //attack
        playSound("BulletWentOff");
    }
}

void BattleObject::setHpbar()
{
    Full=Hp;
    hpBar = new QGraphicsRectItem(0,0, float(width)/10, float(height)/50);
    hpBar->setBrush(QBrush(Qt::red));
    hpBar-> setPos(x(),y()-20);
    game->scene->addItem(hpBar);
}

void BattleObject::cutHpbar()
{

    hpBar->setRect(0,0, (float(width)/10)*((float(Hp)/Full)), float(height)/50);

}
