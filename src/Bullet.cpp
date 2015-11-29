#include "Bullet.h"
#include "Game.h"

extern Game* game;

Bullet::Bullet()
{
    addSound("Hit","://sounds/Hit.wav");
    addSound("Splash","://sounds/splash.wav");
    move_timer = new QTimer();
}

Bullet::~Bullet()
{
    ;
}

Bullet::Bullet(int power): QObject()
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image ?ㅼ젙
    SetAttackPower(power);
    move_timer = new QTimer();
    addSound("Hit","://sounds/Hit.wav");
    addSound("Splash","://sounds/splash.wav");
}

void Bullet::SetAttackPower(int AttackPower)
{
    this->AttackPower = AttackPower;
}

int Bullet::GetAttackPower()
{
    return AttackPower;
}

void Bullet::Activated(bool active)
{
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //?쇱젙 ?쒓컙留덈떎 ?吏곸엫
    if(active)
        move_timer->start(30);
    else
        move_timer->stop();

}
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //enemy??遺?ろ엳硫??щ씪吏?
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            playSound("Hit");               //?곸쨷 ???섎뒗 ?뚮━
            //game->scene->removeItem(colliding_enemies[i]);
            game->scene->removeItem(this);
            //game->SumWithEnemyNum(-1);
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta ?ㅼ젙

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
