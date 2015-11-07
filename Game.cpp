#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BuildTowerIcon.h"
#include <QTimer>
#include "upgrade_button.h"
#include "fusion_button.h"


Game::Game()                    //constructor
{
    scene = new QGraphicsScene(this);       //view하는 scene 생성
    scene->setSceneRect(0,0,1024,768);       //scene 크기 설정
    setScene(scene);

    cursor = nullptr;
    add_mode=false;                        //cursor, add 초기화
    fuse_mode=false;
    upgrade_mode=false;

    setMouseTracking(true);                 //enable mouse tracking
    setFixedSize(1024,768);                  //view 크기 설정

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //scroll 없음

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
    timer->start(2000);


}

void Game::displayMenu()
{
   UpgradeButton *x = new UpgradeButton();
   x->setPos(800-117,100);
   scene->addItem(x);

    BuildTowerIcon *ic = new BuildTowerIcon();
    ic->setPos(800-117,0);
    scene->addItem(ic);                     //add icon 생성

    fusion_button *y = new fusion_button();
    y->setPos(800-117,200);
    scene->addItem(y);
}

void Game::setCursor(QString filename)
{
    if(cursor){                                     //이전에 사용자가 어떤 pixmapitem 오브젝트를 선택 했을 경우
        scene->removeItem(cursor);
        delete cursor;                              //지우고
    }
    cursor = new QGraphicsPixmapItem();             // cursor 생성
    cursor->setPixmap(QPixmap(filename));           //filename의 그림으로
    scene->addItem(cursor);                         //scene에 add
}

void Game::mouseMoveEvent(QMouseEvent *event)       //mouse 움직임
{
    if(cursor){                                     //cursor가 null이 아니면
        cursor->setPos(event->pos());               //cursor를 현재 마우스 위치로
    }
}

void Game::mousePressEvent(QMouseEvent *event)      //mouse 누름
{
    if(add_mode){                                      //add 누른 상태면
        scene->addItem(build[build.size()-1]);
        build[build.size()-1]->setPos(event->pos());                //그자리에 build가 가리키는거 생성
        cursor = nullptr;
        add_mode = false;
    }
    else{
        QGraphicsView::mousePressEvent(event);      //아니면 제기능.
    }
}

void Game::spawnEnemy()
{
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
}
