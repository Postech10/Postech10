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

  //  void setCursor(QString filename);           //모드에 따라 커서를 적절한 그림으로 바꾸게 하는 method

    void mouseMoveEvent(QMouseEvent *event);    //마우스를 움직이는 대로 커서가 움직일 수 있게 하는 method

    void mousePressEvent(QMouseEvent *event);   //모드에 따라 클릭의 기능을 달리하는 method

    QGraphicsPixmapItem *tooltip;

    bool fuse_mode;
    bool upgrade_mode;

    inline void SetAddMode(bool _add_mode) {add_mode = _add_mode;}
    inline bool GetAddMode() {return add_mode;}

    QGraphicsScene *scene;
    QVector<Tower*> waiting_line;


signals:
    void RoundSet(int new_round);

public slots:
    void spawnEnemy();
    void button_Pressed();

private :

    QGraphicsPixmapItem *cursor;                  //members

    QVector<Tower*> build;

    Tower* pointer;

    int round;

    bool add_mode;
    bool position[16][12];

};

#endif // GAME

