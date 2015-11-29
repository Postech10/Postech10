#pragma once
#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include <QVector>
#include <QList>
#include <QString>
#include <QLabel>
#include "Tower.h"
#include "enemy.h"
#include "Wave_Generator.h"
#include "upgrade_button.h"
#include "fusion_button.h"
#include "BuildTowerIcon.h"
#include "button.h"

enum State {Ingame, Paused, Cleared};

class Game: public QGraphicsView{               //game?붾㈃???곸냽 (view)

    Q_OBJECT

public:
    Game();                                     //constructor
    void displayMenu();                         //硫붾돱?ㅼ쓣 異쒕젰?섎뒗 method

    //event method
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    //add_mode accessor & modifier
    inline void SetAddMode(bool _add_mode) {add_mode = _add_mode;}
    inline bool GetAddMode() {return add_mode;}

    //upgrade_mode accessor & modifier
    void SetUpgradeMode(bool _upgrade_mode);
    inline bool GetUpgradeMode() {return upgrade_mode;}

    //money accessor & modifier
    void set_money(int _money);
    inline int get_money() {return money;}

    void SumWithEnemyNum(int _num);
    inline int GetEnemyNum() {return enemy_num;}

    void SetState(int _state);
    int GetState();

    int GetLife() {return life;}
    void SetLife(int _life) {life = _life;}

    void MakeNewGame();

    void FuseTower();

    //吏湲덉? 蹂?섎뱾??public?몃뜲 ?섏쨷??紐⑤몢 private濡?留뚮뱾嫄곗엫.
    QGraphicsScene *scene;
    QList<Tower*> waiting_line;
    QGraphicsPixmapItem *tooltip;
    bool fuse_mode;


signals:
    void RoundSet(int new_round);
    void game_is_cleared();
    //state媛 Cleared濡?諛붾뚯뿀???? ?ㅽ뻾 ?섏뼱 ?ㅼ쓬 ?먯쓣 以鍮??섎뒗 ?⑥닔.

public slots:

    void spawnEnemy();
    void button_Pressed(QPointF point, int tower_code);
    void clear_game();
    void ShowTowerInfo(Tower* tower);
    void DeletTowerInfo();

private :

    QGraphicsPixmapItem *cursor;                  //members

    //round???곕씪 enemy瑜?留뚮뱶???몄뒪?댁뒪
    WaveGenerator wave_generator;
    //???쇱슫?쒖뿉 由ъ뒪???섏뼱???섎뒗 enemy??踰≫꽣
    QVector<Enemy*> SpawnList;
    //吏湲?嫄댁꽕 ????뚮뱾??踰≫꽣
    QVector<Tower*> build;
    //吏湲??꾩옱 由ъ뒪????enemy媛 ?닿릿 踰≫꽣
    QVector<Enemy*> enemy;
    //吏湲??댁븘 ?덈뒗 enemy????
    int enemy_num;
    //二쎌? enemy????
    int dead_enemy;

    //combnination[r][w]媛 true硫?r怨?w??議고빀??媛?ν븿
    bool combination[14][14];

    //??뚮? 嫄댁꽕 ?????ъ슜?섎뒗 ?ъ씤??蹂??
    Tower* pointer;

    int life; //?⑥? 泥대젰
    int money; //怨⑤뱶 ?띾뱷???뺣낫
    int round; //?꾩옱 ?쇱슫??
    int wave; //???쇱슫?쒖뿉 ?깆옣?섎뒗 enemy????
    int state; //?꾩옱 寃뚯엫 ?곹솴???대뼡 ?곹솴?몄? ?뚮젮 二쇰뒗 蹂??

    bool add_mode; //add_mode ?몄? ?꾨땶吏??????뺣낫瑜??닿퀬 ?덈뒗 蹂??
    bool upgrade_mode;
    bool position[16][12]; //1024*768瑜?64*64 ?ш린???뺤궗媛곹삎?ㅻ줈 ?섎닎

    Button *start_pause_button; //start_puase 踰꾪듉
    Fusion_Button *fusion_button; //?⑹껜 踰꾪듉
    BuildTowerIcon *Normal_Tower_button; //???踰꾪듉
    BuildTowerIcon *Splash_Tower_button; //???踰꾪듉
    BuildTowerIcon *Slow_Tower_button; //???踰꾪듉
    BuildTowerIcon *Poison_Tower_button; //???踰꾪듉
    BuildTowerIcon *Chain_Tower_button; //???踰꾪듉
    BuildTowerIcon *Gold_Tower_button; //???踰꾪듉
    UpgradeButton *upgrade_button; //?낃렇?덉씠??踰꾪듉

    QTimer *spawn_timer; //?곷뱾??scene??異쒗쁽 ?섎뒗 frequency??愿???뺣낫瑜??닿퀬 ?덈떎.
    QLabel* round_label; //round 異쒕젰
    QLabel* money_label; //money 異쒕젰

    QGraphicsTextItem* upgrade_level;
    QGraphicsTextItem* attack_ability;
    QGraphicsTextItem* defense_ability;
    QGraphicsTextItem* attack_speed_ability;

};

#endif // GAME

