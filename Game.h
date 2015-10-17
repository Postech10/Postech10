#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include "Tower.h"

class Game: public QGraphicsView{               //game화면을 상속 (view)
    Q_OBJECT
public:
    Game();                                     //constructor
    void displayMenu();
    void setCursor(QString filename);           //cursor생성
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);   //press, move method
    QGraphicsScene *scene;                      //members
    QGraphicsPixmapItem *cursor;
    Tower *build;
public slots:
    void spawnEnemy();
};

#endif // GAME

