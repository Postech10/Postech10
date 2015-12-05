#include "Bullet.h"
#include "Game.h"
#include <QBitmap>

extern Game* game;

Bullet::Bullet()
{
    addSound("Hit","resources/sounds/Hit.wav");
    addSound("Splash","resources/sounds/splash.wav");
    move_timer = new QTimer();
}

Bullet::~Bullet()
{
    delete move_timer;
}

Bullet::Bullet(int power): QObject()
{
    QPixmap image("://images/Bullet_Normal.bmp");
    image.setMask(image.createMaskFromColor(QColor(255,0,170)));
    setPixmap(image);
    SetAttackPower(power);
    move_timer = new QTimer();
    addSound("Hit","resources/sounds/Hit.wav");
    addSound("Splash","resources/sounds/splash.wav");
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
        if((typeid(*(colliding_enemies[i]))==typeid(Enemy))||typeid(*(colliding_enemies[i]))==typeid(AttackableEnemy)){
            if(typeid(*(colliding_enemies[i]))==typeid(Enemy))
                dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            else if(typeid(*(colliding_enemies[i]))==typeid(AttackableEnemy))
                dynamic_cast<AttackableEnemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            playSound("Hit");               //sound for hit
            game->scene->removeItem(this);
            QTimer::singleShot(3000,this,SLOT(callDestructor()));
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

void Bullet::callDestructor()
{
    delete this;
}
