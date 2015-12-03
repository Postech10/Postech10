#include "SplashBullet.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;

SplashBullet::SplashBullet(int power)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SetAttackPower(power);
}

void SplashBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Bullet collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //if enemy
            QGraphicsEllipseItem *SplashRange = new QGraphicsEllipseItem(QRectF(0,0,SPLASH_SCALE_FACTOR,SPLASH_SCALE_FACTOR),this);
            SplashRange->setPen(QPen(Qt::DotLine));     //splash range dot line
            QPointF poly_center(SPLASH_SCALE_FACTOR/2,SPLASH_SCALE_FACTOR/2);               //center of splash range
            poly_center = mapToScene(poly_center);
            QPointF object_center(x()+40,y()+50);       //bullet's position
            QLineF ln(poly_center, object_center);
            SplashRange->setPos(x()+ln.dx(),y()+ln.dy());       //sync center
            QList<QGraphicsItem *> splashed_enemies= SplashRange->collidingItems();     //all items in splash range
            for (size_t j=0, n=splashed_enemies.size();j<n;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy))                       //if enemy
                   dynamic_cast<Enemy*>(splashed_enemies[j])->IsHitBy(AttackPower);     //hit by
            }
            dynamic_cast<Enemy*>(colliding_enemies[i])->IsHitBy(AttackPower);
            playSound("Splash");               //sound for splash
            game->scene->removeItem(this);
            game->scene->removeItem(SplashRange);
            delete SplashRange;
            delete this;
            return;
        }
    }
    double theta = rotation();                      //set theta

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}


