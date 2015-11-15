#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"
#include "Bullet.h"
#include "enemy.h"
#include "BuildTowerIcon.h"
#include <QTimer>
#include "upgrade_button.h"
#include "fusion_button.h"
#include <QPoint>
#include <QDebug>
#include <Qpainter>

Game::Game(){                    //constructor
    scene = new QGraphicsScene(this);       //view하는 scene 생성
    scene->setSceneRect(0,0,1024,768);       //scene 크기 설정
    setScene(scene);

    cursor = nullptr;
    add_mode=false;                        //cursor, add 초기화
    fuse_mode=false;
    upgrade_mode=false;
    for(int i=0 ; i < 16 ; i++){
        for(int j=0 ; j < 12 ; j++)
            position[i][j]=false;
    }

    setMouseTracking(true);                 //enable mouse tracking
    setFixedSize(1024,768);                  //view 크기 설정

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //scroll 없음

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
    timer->start(2000);


    for(int i=0 ; i<13 ; i++){
        QLine line(0,i*64,1024,i*64);
        scene->addLine(line);
    }
    for(int i=0 ; i<17 ; i++){
        QLine line(i*64,0,i*64,768);
        scene->addLine(line);
    }
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

void Game::setCursor(QString filename){
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
        cursor->setPos(event->pos().x()-32,event->pos().y()-32);               //cursor를 현재 마우스 위치로
    }
}

void Game::mousePressEvent(QMouseEvent *event)      //mouse 누름
{
    QPoint pointed_spot = event->pos();
    qDebug()<<pointed_spot.x()/64 << pointed_spot.y()/64;

    if(this->position[pointed_spot.x()/64][pointed_spot.y()/64] == false && add_mode){                                         //add 누른 상태면

        build[build.size()-1]->setPos((pointed_spot.x()/64)*63+32,(pointed_spot.y()/64)*63+32); //그자리에 build가 가리키는거 생성
        scene->addItem(build[build.size()-1]);
    //    cursor->setPos((pointed_spot.x()/64)*64+32,(pointed_spot.y()/64)*64+32);
    //    scene->addItem(cursor);
    //    delete cursor;

        cursor = nullptr;
        add_mode = false;
        this->position[pointed_spot.x()/64][pointed_spot.y()/64] = true;
    }
    else
       QGraphicsView::mousePressEvent(event);
}

void Game::spawnEnemy()
{
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
}
