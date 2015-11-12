#pragma once
#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>
#include "Tower.h"
#include "Enemy.h"
#include "Wave_Generator.h"
#include "upgrade_button.h"
#include "Fusion_Button.h"
#include "BuildTowerIcon.h"
#include "Button.h"

enum State {Ingame, Paused, Cleared};

class Game: public QGraphicsView{               //game화면을 상속 (view)

    Q_OBJECT

public:
    Game();                                     //constructor
    void displayMenu();                         //메뉴들을 출력하는 method

    void mouseMoveEvent(QMouseEvent *event);    //마우스를 움직이는 대로 커서가 움직일 수 있게 하는 method
    void mousePressEvent(QMouseEvent *event);   //모드에 따라 클릭의 기능을 달리하는 method

    inline void SetAddMode(bool _add_mode) {add_mode = _add_mode;}
    inline bool GetAddMode() {return add_mode;}

    void MakeNewGame();

    QGraphicsScene *scene;
    QVector<Tower*> waiting_line;
    QGraphicsPixmapItem *tooltip;
    bool fuse_mode;
    bool upgrade_mode;

    inline void UpdateGame() {round++;}


signals:
    void RoundSet(int new_round);

public slots:

    void spawnEnemy();
    void button_Pressed(QPointF point);

private :

    QGraphicsPixmapItem *cursor;                  //members

    WaveGenerator wave_generator;
    QVector<Enemy*> SpawnList;
    QVector<Tower*> build;
    QVector<Enemy*> enemy;
    int Enemy_size;

    Tower* pointer;

    int round;
    int wave;
    int state;

    bool add_mode;
    bool position[16][12];

    Button *start_pause_button;
    Fusion_Button *fusion_button;
    BuildTowerIcon *tower_button;
    UpgradeButton *upgrade_button;

    QTimer *timer;


};

#endif // GAME

