#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include "Tower.h"
#include <QVector>

class Game: public QGraphicsView{               //game화면을 상속 (view)

    Q_OBJECT

public:
    Game();                                     //constructor

    void displayMenu();                         //메뉴들을 출력하는 method

    void setCursor(QString filename);           //모드에 따라 커서를 적절한 그림으로 바꾸게 하는 method

    void mouseMoveEvent(QMouseEvent *event);    //마우스를 움직이는 대로 커서가 움직일 수 있게 하는 method

    void mousePressEvent(QMouseEvent *event);   //모드에 따라 클릭의 기능을 달리하는 method

    QGraphicsPixmapItem *cursor;
    QVector<Tower*> build;
    QGraphicsScene *scene;                      //members
    bool add_mode;
    bool fuse_mode;
    bool upgrade_mode;
    QVector<Tower*> fuse_tower;

public slots:
    void spawnEnemy();
};

#endif // GAME

