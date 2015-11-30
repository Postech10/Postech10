#include "SplashLaser.h"
#include <typeinfo>
#include "Game.h"

extern Game* game;

SplashLaser::SplashLaser(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //set image
    SetAttackPower(attack);
    GoldPower = gold;
}

void SplashLaser::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Laser collides
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //if enemy
            QGraphicsEllipseItem *SplashRange = new QGraphicsEllipseItem(QRectF(0,0,SPLASH_SCALE_FACTOR,SPLASH_SCALE_FACTOR),this);
            SplashRange->setPen(QPen(Qt::DotLine));     //splash range dot line
            QPointF poly_center(SPLASH_SCALE_FACTOR/2,SPLASH_SCALE_FACTOR/2);               //center of splash range
            poly_center = mapToScene(poly_center);
            QPointF object_center(colliding_enemies[i]->x(),colliding_enemies[i]->y());       //enemy's position that hit by bullet
            QLineF ln(poly_center, object_center);
            SplashRange->setPos(x()+ln.dx(),y()+ln.dy());       //sync center
            QList<QGraphicsItem *> splashed_enemies= SplashRange->collidingItems();         //all items in splash range
            for (size_t j=0, n=splashed_enemies.size();j<n;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy)){                          //if enemy
                    dynamic_cast<Enemy*>(splashed_enemies[j])->IsHitBy(AttackPower);
                    if(dynamic_cast<Enemy*>(colliding_enemies[j])->DieOrNot())              //die?
                        game->set_money(game->get_money()+GoldPower);                       //inc money
                }
            }
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

