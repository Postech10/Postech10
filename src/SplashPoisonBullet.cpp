#include "SplashPoisonBullet.h"
#include <typeinfo> //in strict c++ environment, You SHOULD include <typeinfo> to use typeid
#include "Game.h"

extern Game* game;

SplashPoisonBullet::SplashPoisonBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image ?ㅼ젙
    SetAttackPower(attack);
    GoldPower = gold;
}

void SplashPoisonBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Laser? 遺?ろ엺 item??
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //?대뱾??Enemy?쇰븣
            QGraphicsEllipseItem *SplashRange = new QGraphicsEllipseItem(QRectF(0,0,SPLASH_SCALE_FACTOR,SPLASH_SCALE_FACTOR),this);
            SplashRange->setPen(QPen(Qt::DotLine));     //?먯꽑?쇰줈 踰붿쐞 蹂댁씠湲?
            QPointF poly_center(SPLASH_SCALE_FACTOR/2,SPLASH_SCALE_FACTOR/2);               //SplashRange??以묒떖
            poly_center = mapToScene(poly_center);
            QPointF object_center(colliding_enemies[i]->x(),colliding_enemies[i]->y());       //留욎? ?곸쓽 ?꾩튂
            QLineF ln(poly_center, object_center);
            SplashRange->setPos(x()+ln.dx(),y()+ln.dy());       //center 留욎텛湲?
            QList<QGraphicsItem *> splashed_enemies= SplashRange->collidingItems();//splash踰붿쐞 ?덉뿉?덈뒗 item??
            for (size_t j=0, n=splashed_enemies.size();j<n;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy)){
                    dynamic_cast<Enemy*>(splashed_enemies[j])->IsPoisonedBy(AttackPower); //enemy ?낃구?ㅼ꽌 二쎌?嫄???踰꾨뒗嫄??쇱쓽?꾩슂
                  //  if(dynamic_cast<Enemy*>(splashed_enemies[j])->DieOrNot())       //二쎌뿀?붿? ?꾨땶吏 ?뺤씤?꾩슂.. ?쇱쓽?꾩슂??
                    //Please Add these methods.
                    //game->set_money(game->get_money()+GoldPower);                      //?댄??뚯뿉 ?섑빐 二쎌뿀?꾨븣!! ???щ씪媛?
                }
            }
            playSound("Splash");               //?곸쨷 ???섎뒗 ?뚮━
            game->scene->removeItem(this);                      //瑗?븘?뷀븳吏 紐⑤Ⅴ寃좎쓬.. ?섏쨷???섏젙?덉젙
            game->scene->removeItem(SplashRange);               //留덉갔媛吏
            delete SplashRange;
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta ?ㅼ젙

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}

