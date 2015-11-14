#pragma once
#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>
#include <QString>
#include <QLabel>
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

    //event method
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    //add_mode accessor & modifier
    inline void SetAddMode(bool _add_mode) {add_mode = _add_mode;}
    inline bool GetAddMode() {return add_mode;}

    //money accessor & modifier
    inline void set_money(int _money) {money = _money;}
    inline int get_money() {return money;}

    //게임이 종료 되었을 때, round를 변화 시키는 함수
    inline void UpdateGame() {round++;}

    void SumWithEnemyNum(int _num);
    inline int GetEnemyNum() {return enemy_num;}

    void SetState(int _state);
    int GetState();

    void MakeNewGame();

    //지금은 변수들이 public인데 나중에 모두 private로 만들거임.
    QGraphicsScene *scene;
    QVector<Tower*> waiting_line;
    QGraphicsPixmapItem *tooltip;
    bool fuse_mode;
    bool upgrade_mode;



signals:
    void RoundSet(int new_round);

    void game_is_cleared();
    //state가 Cleared로 바뀌었을 때, 실행 되어 다음 판을 준비 하는 함수.

public slots:

    void spawnEnemy();
    void button_Pressed(QPointF point);
    void clear_game();

private :

    QGraphicsPixmapItem *cursor;                  //members

    //round에 따라 enemy를 만드는 인스턴스
    WaveGenerator wave_generator;
    //한 라운드에 리스폰 되어야 하는 enemy의 벡터
    QVector<Enemy*> SpawnList;
    //지금 건설 된 타워들의 벡터
    QVector<Tower*> build;
    //지금 현재 리스폰 된 enemy가 담긴 벡터
    QVector<Enemy*> enemy;
    //지금 살아 있는 enemy의 수
    int enemy_num;

    //타워를 건설 할 때 사용하는 포인터 변수
    Tower* pointer;

    int life; //남은 체력
    int money; //골드 획득량 정보
    int round; //현재 라운드
    int wave; //한 라운드에 등장하는 enemy의 수
    int state; //현재 게임 상황이 어떤 상황인지 알려 주는 변수

    bool add_mode; //add_mode 인지 아닌지에 대한 정보를 담고 있는 변수
    bool position[16][12]; //1024*768를 64*64 크기의 정사각형들로 나눔

    Button *start_pause_button; //start_puase 버튼
    Fusion_Button *fusion_button; //합체 버튼
    BuildTowerIcon *tower_button; //타워 버튼
    UpgradeButton *upgrade_button; //업그레이드 버튼

    QTimer *spawn_timer; //적들이 scene에 출현 하는 frequency에 관한 정보를 담고 있다.
    QLabel* round_label; //round 출력
    QLabel* money_label; //money 출력
};

#endif // GAME

