#pragma once
#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMovie>
#include <QVector>
#include <QList>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "Tower.h"
#include "enemy.h"
#include "Wave_Generator.h"
#include "upgrade_button.h"
#include "fusion_button.h"
#include "BuildTowerIcon.h"
#include "button.h"
#include "control_animation.h"
#include "professoranimation.h"

enum State {Ingame, Paused, Cleared, GameOver, END};
enum TOWERINFO {BASE,LEVEL2,LEVEL3};

class Game: public QGraphicsView{

    Q_OBJECT

public:
    Game();                                     //constructor
    void displayMenu();                         // display UI

    //event method
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    //add_mode accessor & modifier
    inline void SetAddMode(bool _add_mode) {add_mode = _add_mode;}
    inline bool GetAddMode() {return add_mode;}

    //fuse_mode accessor & modifier
    inline void SetFuseMode(bool _fuse_mode) {fuse_mode = _fuse_mode;}
    inline bool GetFuseMode() {return fuse_mode;}

    //upgrade_mode accessor & modifier
    void SetUpgradeMode(bool _upgrade_mode);
    inline bool GetUpgradeMode() {return upgrade_mode;}

    //money accessor & modifier
    void set_money(int _money);
    inline int get_money() {return money;}

    //round accessor & modifier
    void set_round(int _round);
    inline int get_round() {return round;}

    //renew the number of enemies
    void RenewEnemyNum(bool is_dead);

    //accesor for enemy_num
    inline int GetEnemyNum() {return enemy_num;}

    //state accessor & modifier
    void SetState(int _state);
    int GetState();

    //life accessor & modifier
    int GetLife() {return life;}
    void SetLife(int _life);

    //towerinfo accessor & modifier
    int GetTowerinfo() {return towerinfo;}
    void SetTowerinfo(int _towerinfo) {towerinfo = _towerinfo;}

    //accessors for BuildTowerIcons
    BuildTowerIcon *getNormal_Tower_button() {return Normal_Tower_button;}
    BuildTowerIcon *getSplash_Tower_button() {return Splash_Tower_button;}
    BuildTowerIcon *getSlow_Tower_button() {return Slow_Tower_button;}
    BuildTowerIcon *getGo_to_back_Button() {return Go_to_back_Button;}
    BuildTowerIcon *getPoison_Tower_button() {return Poison_Tower_button;}
    BuildTowerIcon *getChain_Tower_button() {return Chain_Tower_button;}
    BuildTowerIcon *getGold_Tower_button() {return Gold_Tower_button;}
    BuildTowerIcon *getRandom_Tower_Button() {return Random_Tower_Button;}

    //make and prepare next round
    void MakeNewGame();

    //fuse two tower if the combination is available
    bool FuseTower();

    //destroy a tower which was dead
    void DestroyTower(Tower*target);

    //make animation of objects in the scene
    Control_Animation* control;

    //scene which is shown
    QGraphicsScene *scene;

    //waiting list of the towers for upgrade and combination
    QList<Tower*> waiting_line;



signals:
    //a signal emitted when all enemies are removed from the scene
    void game_is_cleared();

    //a signal emitted when game is over
    void game_is_over();

public slots:

    //spawn enemy regularly
    void spawnEnemy();
    //act when button was pressed
    void button_Pressed(QPointF point, int tower_code);
    //clear the current round
    void clear_game();
    //show tower information when a tower is selected
    void ShowTowerInfo(Tower* tower);
    //show hide information when a tower is selected
    void DeletTowerInfo();
    //act when cheat key is entered
    void CheatKeyEntered();
    //clear the current game ane prepare new game
    void destroy_game();
    //make animation for buttons
    void change();
    //make hidden stage round
    void MakeHiddenGame();

private :

    QGraphicsPixmapItem *cursor;
    //make enemies
    WaveGenerator wave_generator;
    //store enemies which are ready to be spawned
    QVector<Enemy*> SpawnList;
    //stor towers in the map
    QVector<Tower*> build;
    //store enemies which was already spawned
    QVector<Enemy*> enemy;
    //the number of enemies was already spawned
    int enemy_num;
    //the number of enemies which were dead
    int dead_enemy;

    //combnination[r][w] is true if a tower whose code is r and the other whose code is w can be combined
    bool combination[14][14];

    //the edit box which user can enter cheat key on it
    QLineEdit* textBox;

    //pointer for tower
    Tower* pointer;

    int life;       //life
    int money;      //money
    int round;      //stage
    int wave;       //the number of enemies which should be spawned
    int state;      //state of game
    int towerinfo;  //state of tooltip

    bool add_mode;          //true when add mode
    bool upgrade_mode;      //true when upgrade mode
    bool fuse_mode;         //true when fuse mode
    bool position[16][12];  //position[m][n] is true if there is already a tower at (64*m , 64*n)

    Button *start_pause_button;         //start_button
    Fusion_Button *fusion_button;       //fusion button
    UpgradeButton *upgrade_button;      //upgrade button

    BuildTowerIcon *Normal_Tower_button;    //normal tower button
    BuildTowerIcon *Splash_Tower_button;    //splash tower button
    BuildTowerIcon *Slow_Tower_button;      //slow tower button
    BuildTowerIcon *Go_to_back_Button;      //go to back button
    BuildTowerIcon *Poison_Tower_button;    //posion tower button
    BuildTowerIcon *Chain_Tower_button;     //chain tower button
    BuildTowerIcon *Gold_Tower_button;      //gold tower button
    BuildTowerIcon *Random_Tower_Button;    //random tower button

    QGraphicsPixmapItem* map;               //map
    QGraphicsPixmapItem* hidden;            //hidden stage map

    QTimer *spawn_timer;                    //act when the enemies are spawned
    QLabel* round_label;                    //show current stage the user is in
    QLabel* money_label;                    //show current money the user has
    QGraphicsRectItem* hpBar;               //show current hp

    QLabel* attack_ability;                 //show attack level of a tower selected
    QLabel* defense_ability;                //show defense level of a tower selected
    QLabel* attack_speed_ability;           //show attack speed level of a tower selected
    QLabel* game_over;                      //show game over sign
    QLabel *tooltip;                        //to show tooltip

    QMovie* movie_tooltip;                  //a tooltip movie
    int num_mouseonbutton;                  //a number to point in what icon the mouse is
    QGraphicsProxyWidget* widget_tooltip;   //a proxy widget pointer to store converted widget.
    //pointers to atk, atkspd, def QLebels.
    QGraphicsProxyWidget* widget_atk;
    QGraphicsProxyWidget* widget_atkspd;
    QGraphicsProxyWidget* widget_def;
    ProfessorAnimation professor_animation;

    //to play BGM
    QMediaPlayer player;
    QMediaPlaylist playlist;

    bool isgameon;
};

#endif // GAME

