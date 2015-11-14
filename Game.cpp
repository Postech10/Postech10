#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BuildTowerIcon.h"
#include <QTimer>


Game::Game()                    //constructor
{
    scene = new QGraphicsScene(this);       //view하는 scene 생성
    scene->setSceneRect(0,0,800,600);       //scene 크기 설정
    setScene(scene);
    cursor = nullptr;
    build = nullptr;                        //cursor, build 초기화
    setMouseTracking(true);                 //enable mouse tracking
    setFixedSize(800,600);                  //view 크기 설정
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //scroll 없음
    BuildTowerIcon *ic = new BuildTowerIcon();
    ic->setPos(800-117,0);
    scene->addItem(ic);                     //add icon 생성

    //button 하나 생성


    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
    timer->start(2000);


}

void Game::setCursor(QString filename)
{
    if(cursor){                                     //cursor가 이미 있으면
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
    if(build){                                      //add 누른 상태면
        scene->addItem(build);
        build->setPos(event->pos());                //그자리에 build가 가리키는거 생성
        cursor = nullptr;
        build = nullptr;                            //다시 초기화
    }
    else{
        QGraphicsView::mousePressEvent(event);      //아니면 제기능
    }
}

void Game::spawnEnemy()
{
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
}
