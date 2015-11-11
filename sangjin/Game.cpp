#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
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

    tooltip = nullptr;
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
    x->setPos(1024-192,500);
    x->setZValue(1);
    scene->addItem(x);

    BuildTowerIcon *ic = new BuildTowerIcon(":/images/Mechanical.bmp");
    ic->setPos(1024-192,0);
    ic->setZValue(1);
    scene->addItem(ic);                     //add icon 생성

    fusion_button *y = new fusion_button();
    y->setPos(1024-192+64,500);
    y->setZValue(1);
    scene->addItem(y);

    scene->addRect(1024-192,0,200,768,QPen(Qt::SolidLine),QBrush(QColor(Qt::gray)));
}

/*void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(event->pos().x()/64 == 16 && event->pos().y()/64 == )
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
*/
void Game::mouseMoveEvent(QMouseEvent *event)       //mouse 움직임
{
    if(tooltip){
        scene->removeItem(tooltip);
        delete tooltip;
        tooltip = nullptr;
    }

    if(event->pos().x()/64 == (1024-192)/64 && event->pos().y()/64 == 0){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/add.png"));
        tooltip->setPos(1024-192,300);
        scene->addItem(tooltip);
    }

    else
        QGraphicsView::mouseMoveEvent(event);
}

void Game::spawnEnemy()
{
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);
}

void Game::button_Pressed()
{
    if(add_mode == true){
        build.push_back(new Tower());
        QPixmap* add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));
        QCursor* add_mode_cursor = new QCursor(*add_mode_pixmap);
        QWidget::setCursor(*add_mode_cursor);
    }
}

void Game::mousePressEvent(QMouseEvent *event){

    QPoint pointed_spot = event->pos();

    if(this->position[pointed_spot.x()/64][pointed_spot.y()/64] == false && add_mode){
        pointer = build[build.size()-1];
        pointer->setVisible(true);
        pointer->setPos((pointed_spot.x()/64)*64,(pointed_spot.y()/64)*64);
        scene->addItem(pointer);
        QWidget::unsetCursor();

        this->position[pointed_spot.x()/64][pointed_spot.y()/64] = true;
        add_mode = false;
    }
    else
       QGraphicsView::mousePressEvent(event);
}
