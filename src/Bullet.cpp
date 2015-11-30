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
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
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
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));        //moving with timer
    if(active)
        move_timer->start(30);
    else
        move_timer->stop();

}
void Bullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //bullet collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            playSound("Hit");               //sound for hit
            game->scene->removeItem(this);
            delete this;
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
