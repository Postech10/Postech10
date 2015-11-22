#include "SplashPoisonBullet.h"
#include <typeinfo> //in strict c++ environment, You SHOULD include <typeinfo> to use typeid
#include "Game.h"

extern Game* game;

SplashPoisonBullet::SplashPoisonBullet(int attack, int gold)
{
    setPixmap(QPixmap(":/images/Mechanical.bmp"));          //image 설정
    SetAttackPower(attack);
    GoldPower = gold;
}

void SplashPoisonBullet::move()
{
    QList<QGraphicsItem *> colliding_enemies=collidingItems();      //Splash Laser와 부딪힌 item들
    for(size_t i=0, n=colliding_enemies.size();i<n;i++){
        if(typeid(*(colliding_enemies[i]))==typeid(Enemy)){         //이들이 Enemy일때
            QVector<QPointF> points;                             //SplashRange 설정 과정
            points << QPoint(1,0)<< QPoint(2,0)<< QPoint(3,1)<< QPoint(3,2)<< QPoint(2,3)
                      << QPoint(1,3)<< QPoint(0,2)<< QPoint(0,1);//스플래쉬 범위 설정 -> 나중에 원으로 하는법 알아내면 바꿀예정 지금은 8각형임..
            for (size_t k=0, n=points.size(); k<n;k++)
                points[k]*=SPLASH_SCALE_FACTOR;                    //스플래쉬 크기만큼 확대
            QGraphicsPolygonItem* SplashRange = new QGraphicsPolygonItem(QPolygonF(points),this);
            SplashRange->setPen(Qt::DotLine);     //점선으로 범위 보이기
            QPointF poly_center(1.5,1.5);               //SplashRange의 중심
            poly_center *= SPLASH_SCALE_FACTOR;                //역시 확대
            poly_center = mapToScene(poly_center);
            QPointF object_center(colliding_enemies[i]->x(),colliding_enemies[i]->y());       //맞은 적의 위치
            QLineF ln(poly_center, object_center);
            SplashRange->setPos(x()+ln.dx(),y()+ln.dy());       //center 맞추기
            QList<QGraphicsItem *> splashed_enemies= SplashRange->collidingItems();//splash범위 안에있는 item들
            for (size_t j=0, n=splashed_enemies.size();j<n;j++){
                if(typeid(*(splashed_enemies[j]))==typeid(Enemy)){
                   // dynamic_cast<Enemy*>(splashed_enemies[j])->IsPoisonedBy(AttackPower); //enemy 독걸려서 죽은거 돈 버는거 논의필요
                  //  if(dynamic_cast<Enemy*>(splashed_enemies[j])->DieOrNot())       //죽었는지 아닌지 확인필요.. 논의필요함
                    //Please Add these methods.
                	game->set_money(game->get_money()+GoldPower);                      //이타워에 의해 죽었을때!! 돈 올라감            
                }
            }
            game->scene->removeItem(this);                      //꼭필요한지 모르겠음.. 나중에 수정예정
            game->scene->removeItem(SplashRange);               //마찬가지
            delete SplashRange;
            delete this;
            return;
        }
    }
    double theta = rotation();                      //theta 설정

    double dy = STEP_SIZE*qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE*qCos(qDegreesToRadians(theta));

    setPos(x()+dx,y()+dy);
}
