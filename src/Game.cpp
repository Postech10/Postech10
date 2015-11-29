#include "Game.h"
#include <QGraphicsScene>
#include "Tower.h"
#include "Bullet.h"
#include "enemy.h"
#include "BuildTowerIcon.h"
#include <QTimer>
#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <sstream>

Game::Game(){
    scene = new QGraphicsScene(this);       //make scene
    scene->setSceneRect(0,0,1024,768);      //set size of scene
    setFixedSize(1024,768);                 //fiz size of scene
    setScene(scene);

    life = 100;
    money = 50;                             //money given at first
    round = 1;                              //initialize round
    tooltip = nullptr;                      //initialize tooltip
    cursor = nullptr;                       //initialize cursor

    add_mode=false;                         //initialize modes
    fuse_mode=false;
    //upgrade_mode=false;

    state = Cleared;                        //initialize state
    enemy_num=0;
    dead_enemy=0;
    wave=0;

    for(int i=0 ; i < 11 ; i++){
        for(int j=0 ; j < 12 ; j++)
            position[i][j]=false;
    }
    for(int i=11 ; i < 16 ; i++){
        for(int j=0 ; j < 12 ; j++)
            position[i][j]=true;
    }
    for(int i=3 ; i<10 ; i++)
        position[i][7]=true;
    position[3][8]=true;
    for(int i=3 ; i<9 ; i++)
        position[i][9]=true;
    for(int i=4 ; i<9 ; i++)
        position[i][2]=true;
    for(int i=2 ; i<8 ; i++)
        position[9][i]=true;
    for(int i=0 ; i<16; i++)
        position[i][0]=true;

    setMouseTracking(true);                 //enable mouse tracking
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //prohibit using scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i=0 ; i<14 ; i++){
        for(int j=0 ; j<14 ; j++)
            combination[i][j]=false;
    }
    combination[0][0]=true; //디버깅용
    combination[0][2]=true;
    combination[1][4]=true;
    combination[1][5]=true;
    combination[3][5]=true;
    combination[4][5]=true;
    combination[6][9]=true;
    combination[7][9]=true;
    combination[8][10]=true;

    combination[2][0]=true;
    combination[4][1]=true;
    combination[5][1]=true;
    combination[5][3]=true;
    combination[5][4]=true;
    combination[9][6]=true;
    combination[9][7]=true;
    combination[10][8]=true;

    //when game is cleared, automatically the game objcet prepares the next rounds.
    connect(this,SIGNAL(game_is_cleared()),this,SLOT(clear_game()));
}

//method to display default Menu on the scene
//this method is called right after the program is run
void Game::displayMenu()
{
    QPixmap* map = new QPixmap(":/images/Map.bmp");
    scene->addPixmap(*map);

    //make upgrade button and add it into scene
    upgrade_button = new UpgradeButton(":/images/upgrade.jpg");
    upgrade_button->setPos(1024-64*2-20,550);
    upgrade_button->setZValue(1);
    scene->addItem(upgrade_button);

    //make build tower buttons and add it into scene
    Normal_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",NORMAL);
    Normal_Tower_button->setPos(1024-32*3,32*3);
    Normal_Tower_button->setZValue(1);
    scene->addItem(Normal_Tower_button);                     //add icon 생성

    Splash_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",SPLASH);
    Splash_Tower_button->setPos(1024-32*6,32*3);
    Splash_Tower_button->setZValue(1);
    scene->addItem(Splash_Tower_button);

    Slow_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",SLOW);
    Slow_Tower_button->setPos(1024-32*9,32*3);
    Slow_Tower_button->setZValue(1);
    scene->addItem(Slow_Tower_button);

    Poison_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",POISON);
    Poison_Tower_button->setPos(1024-32*3,32*6);
    Poison_Tower_button->setZValue(1);
    scene->addItem(Poison_Tower_button);

    Chain_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",CHAIN);
    Chain_Tower_button->setPos(1024-32*6,32*6);
    Chain_Tower_button->setZValue(1);
    scene->addItem(Chain_Tower_button);

    Gold_Tower_button = new BuildTowerIcon(":/images/Mechanical.bmp",GOLD);
    Gold_Tower_button->setPos(1024-32*9,32*6);
    Gold_Tower_button->setZValue(1);
    scene->addItem(Gold_Tower_button);

    //make fusion button and add it into scene
    fusion_button = new Fusion_Button(":/images/FUSE.jpg");
    fusion_button->setPos(1024-64*5+20,550);
    fusion_button->setZValue(1);
    scene->addItem(fusion_button);

    //make start button and add it into scene
    start_pause_button = new Button(":/images/start.jpg");
    start_pause_button->setPos(1024-64*4,620);
    start_pause_button->setZValue(1);
    scene->addItem(start_pause_button);

    //make a label which shows current round and add it into scene
    round_label = new QLabel();
    round_label->setFont(QFont("Arial", 20 , QFont::Bold));
    //round_label->setStyleSheet("background-color:gray;");
    round_label->setText(QString("Round ")+QString::number(round));
    round_label->setGeometry(1024-64*4,0,64*3,30);
    scene->addWidget(round_label);

    //make a label which shows current money the user has and add it into scene
    money_label = new QLabel();
    money_label->setFont(QFont("Arial", 20 , QFont::Bold));
    //money_label->setStyleSheet("background-color:gray;");
    money_label->setText(QString("Money ")+QString::number(money));
    money_label->setGeometry(1024-64*4,35,64*3,30);
    scene->addWidget(money_label);
}


//method to controll any mouse move events
//this method is called when a user point the tower button and this shows information of tower which user is looking at
void Game::mouseMoveEvent(QMouseEvent *event)
{

    //if there was a tooltip already
    if(tooltip && waiting_line.size() == 0){
        scene->removeItem(tooltip);
        delete tooltip;
        tooltip = nullptr;
    }

    //when mouse cursor is on tower build button
    if(event->pos().x()-(1024-32*3)<64 && event->pos().y()-32*3<64 && event->pos().x()-(1024-32*3)>0 && event->pos().y()-32*3>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else if(event->pos().x()-(1024-32*6)<64 && event->pos().y()-32*3<64 && event->pos().x()-(1024-32*6)>0 && event->pos().y()-32*3>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else if(event->pos().x()-(1024-32*9)<64 && event->pos().y()-32*3<64 && event->pos().x()-(1024-32*9)>0 && event->pos().y()-32*3>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else if(event->pos().x()-(1024-32*3)<64 && event->pos().y()-32*6<64 && event->pos().x()-(1024-32*3)>0 && event->pos().y()-32*6>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else if(event->pos().x()-(1024-32*6)<64 && event->pos().y()-32*6<64 && event->pos().x()-(1024-32*6)>0 && event->pos().y()-32*6>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else if(event->pos().x()-(1024-32*9)<64 && event->pos().y()-32*6<64 && event->pos().x()-(1024-32*9)>0 && event->pos().y()-32*6>0 && tooltip == nullptr){
        tooltip = new QGraphicsPixmapItem();
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));
        tooltip->setPos(1024-192,280);
        scene->addItem(tooltip);
    }
    else
        QGraphicsView::mouseMoveEvent(event);
}


//method to spawn one enemy.
//the method is called by spaawn timer regularly
void Game::spawnEnemy()
{
    if(SpawnList.size() != enemy.size() ){
        enemy.push_back(SpawnList[SpawnList.size()-enemy.size()-1]);
        wave++;                                    //the number of enemies which were spawned.
        enemy.back()->startMovement();
        //please add startMovement method and un-commentize this.
        scene->addItem(enemy.back());
        enemy_num++;                                //the number of enemies which are alive.
    }
    else
        spawn_timer->stop();
}


//when button was pressed, this method is called
//it acts differently according to current situation
void Game::button_Pressed(QPointF point,int tower_code)
{
    if(add_mode == true){
        QPixmap* add_mode_pixmap;

        switch(tower_code){
        case NORMAL:
            build.push_back(new Tower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp")); break;
        case SPLASH:
            build.push_back(new SplashTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));break;
        case SLOW:
            build.push_back(new SlowTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));break;
        case POISON:
            build.push_back(new PoisonTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));break;
        case CHAIN:
            build.push_back(new ChainTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));break;
        case GOLD:
            build.push_back(new GoldTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Mechanical.bmp"));break;
        }
        QCursor* add_mode_cursor = new QCursor(*add_mode_pixmap);
        QWidget::setCursor(*add_mode_cursor);
    }

    //when start button pressed.
    else if(start_pause_button->contains(point) == true && state == Cleared){
        MakeNewGame();

        spawn_timer = new QTimer(this);
        connect(spawn_timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
        spawn_timer->start(1000);

        scene->removeItem(start_pause_button);
        state = Ingame;
    }
    /*
    else if(start_pause_button->contains(point)==true && state == Ingame){

        if(spawn_timer != nullptr){
            spawn_timer->stop();
            delete spawn_timer;
            spawn_timer = nullptr;
        }

        //for(int i=0 ; i<enemy.size() ; i++)
            //enemy[i]->stopMovement();
        //please declare stopMovement method and un-commentize this

        start_pause_button->setPixmap(QPixmap(":/images/Start_Button.png"));
        state = Paused;
    }

    else if(start_pause_button->contains(point)==true && state == Paused){
        //for(int i=0 ; i<enemy.size() ; i++)
            //enemy[i]->startMovement(150);
        //please declare startMovement method and un-commentize this.

        spawn_timer = new QTimer(this);
        connect(spawn_timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
        spawn_timer->start(2000);

        start_pause_button->setPixmap(QPixmap(":/images/Pause_Button.png"));
        state = Ingame;
    }
    */
}


//method to clear game
//this method is called when all spawned enemies is removed from scene
void Game::clear_game()
{
    wave_generator.ClearSpwanList(wave);
    start_pause_button->setPixmap(QPixmap(":/images/start.jpg"));
    scene->addItem(start_pause_button);

    round++;
    money += dead_enemy*10;

    round_label->setText(QString("Round ")+QString::number(round));
    money_label->setText(QString("Money ")+QString::number(money));

    wave = 0;
    dead_enemy=0;
    enemy_num=0;
}


//method to show an selected tower information
//this method is called when an user selected an tower in map.
void Game::ShowTowerInfo(Tower *tower)
{
    if(tooltip){
        scene->removeItem(tooltip);
        delete tooltip;
        tooltip = nullptr;

        scene->removeItem(attack_ability);
        delete attack_ability;
        attack_ability = nullptr;

        scene->removeItem(defense_ability);
        delete defense_ability;
        defense_ability = nullptr;

        scene->removeItem(attack_speed_ability);
        delete attack_speed_ability;
        attack_speed_ability = nullptr;
    }

    tooltip = new QGraphicsPixmapItem();
    tooltip->setPos(1024-192-32*3,280);

    int towerType = tower->GetTowerCode();
    switch(towerType){

    case NORMAL:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case SPLASH:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case SLOW:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case POISON:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case CHAIN:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case GOLD:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case TUTOR:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case PROF:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case CES:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case MES:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case APPLE:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case JOBS:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;
    case TRIPLE:
        tooltip->setPixmap(QPixmap(":/images/tooltip.png"));break;

    }

    char buff[100];

    sprintf(buff, "%d", tower->GetAttackPower());
    attack_ability = scene->addText(QString("Attack: ")+QString(buff),QFont("Arial", 10));
    attack_ability->setDefaultTextColor(QColor(Qt::white));
    attack_ability->setPos(1024-32*3,32*12);

    sprintf(buff, "%d", tower->GetDefensivePower());
    defense_ability = scene->addText(QString("Defense: ")+QString(buff),QFont("Arial", 10));
    defense_ability->setDefaultTextColor(QColor(Qt::white));
    defense_ability->setPos(1024-32*3,32*13);

    sprintf(buff, "%d", tower->GetAttackSpeed());
    attack_speed_ability = scene->addText(QString("Speed: ")+QString(buff),QFont("Arial", 10));
    attack_speed_ability->setDefaultTextColor(QColor(Qt::white));
    attack_speed_ability->setPos(1024-32*3,32*14);

    scene->addItem(tooltip);
}


//method to hide tower information
//this method is called when we have to hide information of tower
void Game::DeletTowerInfo()
{
    if(tooltip){
        scene->removeItem(tooltip);
        delete tooltip;
        tooltip = nullptr;

        scene->removeItem(attack_ability);
        delete attack_ability;
        attack_ability = nullptr;

        scene->removeItem(defense_ability);
        delete defense_ability;
        defense_ability = nullptr;

        scene->removeItem(attack_speed_ability);
        delete attack_speed_ability;
        attack_speed_ability = nullptr;
    }
}

//method to controll any mouse click events.
//when add mode is true, tower is built by this method.
void Game::mousePressEvent(QMouseEvent *event){

    QPoint pointed_spot = event->pos();

    if(this->position[pointed_spot.x()/64][pointed_spot.y()/64] == false && add_mode){

        pointer = build[build.size()-1];
        pointer->setVisible(true);
        pointer->setPos((pointed_spot.x()/64)*64,(pointed_spot.y()/64)*64);
        pointer->Activated(true);
        scene->addItem(pointer);
        QWidget::unsetCursor();

        this->position[pointed_spot.x()/64][pointed_spot.y()/64] = true;
        add_mode = false;
        money_label->setText(QString("Money ")+QString::number(money));
    }

    else
        QGraphicsView::mousePressEvent(event);
}


//method to modify upgrade mode
void Game::SetUpgradeMode(bool _upgrade_mode)
{
    if(upgrade_mode != _upgrade_mode){
        upgrade_mode = _upgrade_mode;
    }
}


//method to renew the number of enemies which are still alive
//when the number of enemies in the map goes to zero, we change state of game to CLERED
void Game::SumWithEnemyNum(int _num)
{
    enemy_num += _num;
    dead_enemy++;
    qDebug()<<wave<<","<<enemy_num<<","<<dead_enemy;
    if(wave == SpawnList.size() && enemy_num == 0 && dead_enemy == SpawnList.size()){
        SetState(Cleared);
    }
}


//method to make new game when new round of game begins
//we clean enemy & spawn list, renew level and money, and generate new waves.
void Game::MakeNewGame()
{    
    enemy.clear();
    SpawnList.clear();
    SpawnList = wave_generator.MakeSpawnList(round);
}

void Game::FuseTower()
{
    if(waiting_line.size() == 2){

        Tower* new_tower;
        int first = waiting_line[0]->GetTowerCode();
        int second = waiting_line[1]->GetTowerCode();

        if(combination[first][second] == true){
           new_tower = waiting_line[0]->fuseTower(waiting_line[0],waiting_line[1]);
            scene->removeItem(waiting_line[0]);
            scene->removeItem(waiting_line[1]);

            for(int i=0 ; i<build.size() ; i++){
                if(build[i] == waiting_line[0] || build[i] == waiting_line[1])
                    build.remove(i);
            }

            position[static_cast<int>(waiting_line[0]->pos().x()/64)][static_cast<int>(waiting_line[0]->pos().y()/64)] = false;
            position[static_cast<int>(waiting_line[1]->pos().x()/64)][static_cast<int>(waiting_line[1]->pos().y()/64)] = false;

            delete waiting_line[0];
            delete waiting_line[1];
            waiting_line.clear();

            build.push_back(new_tower);
            add_mode = true;
            QPixmap* pixmap;

            switch(new_tower->GetTowerCode()){
            case TUTOR:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case PROF:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case CES:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case MES:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case APPLE:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case JOBS:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            case TRIPLE:
                pixmap = new QPixmap(QString(":/images/tooltip.png"));break;
            }
            QCursor* new_cursor = new QCursor(*pixmap);
            QWidget::setCursor(*new_cursor);

            scene->removeItem(attack_ability);
            delete attack_ability;
            attack_ability = nullptr;

            scene->removeItem(defense_ability);
            delete defense_ability;
            defense_ability = nullptr;

            scene->removeItem(attack_speed_ability);
            delete attack_speed_ability;
            attack_speed_ability = nullptr;


        }
        else
            qDebug()<<"fusion 할 수 없습니다!";
    }

    else
        qDebug()<<"fusion 할 수 없습니다!";




}


//method to modify state of the game
//this mehod emit signal that all enemies are removed from the scene
void Game::SetState(int _state){
    if(state != _state){
        state = _state;
        if(_state == Cleared){
               qDebug()<<"!!!!!11";
            emit game_is_cleared();
        }
    }
}

void Game::set_money(int _money){
    money = _money;
    money_label->setText(QString("Money ")+QString::number(money));
}
