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
#include <QFontDatabase>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>

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
    upgrade_mode=false;

    state = Cleared;                        //initialize state
    towerinfo = BASE;
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

    control = new Control_Animation();

    //when game is cleared, automatically the game objcet prepares the next rounds.
    connect(this,SIGNAL(game_is_cleared()),this,SLOT(clear_game()));
    connect(this,SIGNAL(game_is_over()),this,SLOT(destroy_game()));
}

//method to display default Menu on the scene
//this method is called right after the program is run
void Game::displayMenu()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/PressStart2P.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont mystyle(family);

    QPixmap* map = new QPixmap(":/images/Map.bmp");
    scene->addPixmap(*map);

    //make upgrade button and add it into scene
    upgrade_button = new UpgradeButton(":/images/UpgradeButton.bmp");
    upgrade_button->setPos(768,0);
    upgrade_button->setZValue(1);
    scene->addItem(upgrade_button);

    //make build tower buttons and add it into scene
    Normal_Tower_button = new BuildTowerIcon(":/images/Icon_Assistant.bmp",NORMAL);
    Normal_Tower_button->setPos(768,192);
    Normal_Tower_button->setZValue(1);
    scene->addItem(Normal_Tower_button);

    Splash_Tower_button = new BuildTowerIcon(":/images/Icon_Mechanical.bmp",SPLASH);
    Splash_Tower_button->setPos(768+64,192);
    Splash_Tower_button->setZValue(1);
    scene->addItem(Splash_Tower_button);

    Slow_Tower_button = new BuildTowerIcon(":/images/Icon_SMP.bmp",SLOW);
    Slow_Tower_button->setPos(768+64*2,192);
    Slow_Tower_button->setZValue(1);
    scene->addItem(Slow_Tower_button);

    Go_to_back_Button = new BuildTowerIcon(":/images/Icon_LV2TOWER.bmp",15);
    Go_to_back_Button->setPos(768+64*3,192);
    Go_to_back_Button->setZValue(1);
    scene->addItem(Go_to_back_Button);

    Poison_Tower_button = new BuildTowerIcon(":/images/Icon_Chemical.bmp",POISON);
    Poison_Tower_button->setPos(768,192+64);
    Poison_Tower_button->setZValue(1);
    scene->addItem(Poison_Tower_button);

    Chain_Tower_button = new BuildTowerIcon(":/images/Icon_Electronic.bmp",CHAIN);
    Chain_Tower_button->setPos(768+64,192+64);
    Chain_Tower_button->setZValue(1);
    scene->addItem(Chain_Tower_button);

    Gold_Tower_button = new BuildTowerIcon(":/images/Icon_IME.bmp",GOLD);
    Gold_Tower_button->setPos(768+64*2,192+64);
    Gold_Tower_button->setZValue(1);
    scene->addItem(Gold_Tower_button);

    Random_Tower_Button = new BuildTowerIcon(":/images/Icon_Random.bmp",14);
    Random_Tower_Button->setPos(768+64*3,192+64);
    Random_Tower_Button->setZValue(1);
    scene->addItem(Random_Tower_Button);

    //make fusion button and add it into scene
    fusion_button = new Fusion_Button(":/images/FusionButton.bmp");
    fusion_button->setPos(896,0);
    fusion_button->setZValue(1);
    scene->addItem(fusion_button);

    //make start button and add it into scene
    start_pause_button = new Button(":/images/StartButton.bmp");
    start_pause_button->setPos(768,576);
    start_pause_button->setZValue(1);
    scene->addItem(start_pause_button);

    //make a label which shows current round and add it into scene
    round_label = new QLabel();
    mystyle.setBold(true);
    mystyle.setPointSize(20);
    round_label->setFont(mystyle);
    round_label->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : white; }");
    round_label->setText(QString("Round ")+QString::number(round));
    round_label->setGeometry(704-64*3,704,64*4,64);
    scene->addWidget(round_label);

    //make a label which shows current money the user has and add it into scene
    money_label = new QLabel();
    mystyle.setBold(true);
    mystyle.setPointSize(15);
    money_label->setFont(mystyle);
    money_label->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : rgba(255,234,0); }");
    money_label->setText(QString::number(money));
    money_label->setGeometry(1024-64*2.2,32*10.5,64*3,50);
    scene->addWidget(money_label);

    hpBar = new QGraphicsRectItem();
    hpBar->setBrush(QBrush(Qt::red));
    hpBar->setPos(256,21);
    hpBar->setRect(0,0, (704-256)*((float(life)/100)), float(42-21));
    scene->addItem(hpBar);

    textBox = new QLineEdit();
    connect(textBox , SIGNAL(returnPressed()), this, SLOT(CheatKeyEntered()));
    textBox->setGeometry(768+5 , 710 , 64*3.5 , 32);
    textBox->setStyleSheet("background-color : white;");
    scene->addWidget(textBox);
    num_mouseonbutton = 0;
}


//method to controll any mouse move events
//this method is called when a user point the tower button and this shows information of tower which user is looking at
void Game::mouseMoveEvent(QMouseEvent *event)
{

    //if there was a tooltip already
    /*if(tooltip && waiting_line.size() == 0){
        delete tooltip;
        tooltip = nullptr;
    } */
    //when mouse cursor is on tower build button
    if(waiting_line.size() != 0) return;
    if(event->pos().x()-(768)<64 && event->pos().y()-(192)<64
            && event->pos().x()-(768)>0&& event->pos().y()-(192)>0){
        if(num_mouseonbutton != 1)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }

            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_Assistant.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/TooltipLV2_TutoringMachine.gif");
            else if(towerinfo == LEVEL3)
                movie_tooltip = new QMovie(":/images/TooltipLV3_AppleDeathMachinel.gif");

            if(towerinfo == BASE || towerinfo == LEVEL2 || towerinfo == LEVEL3)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 1;
        }
    }
    else if(event->pos().x()-(768+64)<64 && event->pos().y()-192<64
            && event->pos().x()-(768+64)>0 && event->pos().y()-192>0){
        if(num_mouseonbutton != 2)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_Mechanical.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/TooltipLV2_Session.gif");
            else if(towerinfo == LEVEL3)
                movie_tooltip = new QMovie(":/images/TooltipLV3_JobsDream.gif");

            if(towerinfo == BASE || towerinfo == LEVEL2 || towerinfo == LEVEL3)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 2;
        }
    }
    else if(event->pos().x()-(768+64*2)<64 && event->pos().y()-192<64
            && event->pos().x()-(768+64*2)>0 && event->pos().y()-192>0){
        if(num_mouseonbutton != 3)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_SMP.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/TooltipLV2_ChemEng.gif");
            else if(towerinfo == LEVEL3)
                movie_tooltip = new QMovie(":/images/TooltipLV3_3Major.gif");

            if(towerinfo == BASE || towerinfo == LEVEL2 || towerinfo == LEVEL3)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 3;
        }
    }
    else if(event->pos().x()-(768+64*3)<64 && event->pos().y()-192<64
            && event->pos().x()-(768+64*3)>0 && event->pos().y()-192>0){
        if(num_mouseonbutton != 4)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_ToLevel2Tower.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/Tooltip_ToLevel3Tower.gif");
            else delete tooltip;

            if(towerinfo == BASE || towerinfo == LEVEL2)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 4;
        }
    }
    else if(event->pos().x()-(768)<64 && event->pos().y()-(192+64)<64
            && event->pos().x()-(768)>0 && event->pos().y()-(192+64)>0){
        if(num_mouseonbutton != 5)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_Chemical.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/TooltipLV2_Metal.gif");
            else delete tooltip;

            if(towerinfo == BASE || towerinfo == LEVEL2)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 5;
        }
    }
    else if(event->pos().x()-(768+64)<64 && event->pos().y()-(192+64)<64
            && event->pos().x()-(768+64)>0 && event->pos().y()-(192+64)>0){
        if(num_mouseonbutton != 6)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_Electronics.gif");
            else if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/TooltipLV2_JobsBook.gif");
            else tooltip;

            if(towerinfo == BASE || towerinfo == LEVEL2)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 6;
        }
    }
    else if(event->pos().x()-(768+64*2)<64 && event->pos().y()-(192+64)<64
            && event->pos().x()-(768+64*2)>0 && event->pos().y()-(192+64)>0){
        if(num_mouseonbutton != 7)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_IME.gif");
            else delete tooltip;

            if(towerinfo == BASE)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 7;
        }
    }
    else if(event->pos().x()-(768+64*3)<64 && event->pos().y()-(192+64)<64
            && event->pos().x()-(768+64*3)>0 && event->pos().y()-(192+64)>0){
        if(num_mouseonbutton != 8)
        {
            if(widget_tooltip && tooltip && movie_tooltip){
                scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
                delete tooltip;
                delete movie_tooltip;
                widget_tooltip = nullptr;
                tooltip = nullptr;
                movie_tooltip = nullptr;
            }
            tooltip = new QLabel();
            if(towerinfo == BASE)
                movie_tooltip = new QMovie(":/images/Tooltip_Random.gif");
            if(towerinfo == LEVEL2)
                movie_tooltip = new QMovie(":/images/Tooltip_BackToBaseTowergif.gif");
            if(towerinfo == LEVEL3)
                movie_tooltip = new QMovie(":/images/Tooltip_BackToBaseTowergif.gif");

            if(towerinfo == BASE || towerinfo == LEVEL2 || towerinfo == LEVEL3)
            {
                tooltip->setMovie(movie_tooltip);
                tooltip->movie()->start();
                tooltip->setGeometry(768,384,256,192);
                widget_tooltip = scene->addWidget(tooltip);
            }
            num_mouseonbutton = 8;
        }
    }
    else{
        //When the mouse is out of the tower icons,
        //if the screen has a tooltip. delete it.
        if(widget_tooltip && tooltip && movie_tooltip){
            scene->removeItem(widget_tooltip);//delete previous tooltip from the screen
            delete tooltip;
            delete movie_tooltip;
            widget_tooltip = nullptr;
            tooltip = nullptr;
            movie_tooltip = nullptr;
        }
        num_mouseonbutton = 0;
        QGraphicsView::mouseMoveEvent(event);
    }
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
        control->ADD(enemy.back());
    }
    else
        spawn_timer->stop();
}


//when button was pressed, this method is called
//it acts differently according to current situation
void Game::button_Pressed(QPointF point,int tower_code)
{

    if(add_mode == true && towerinfo == BASE){
        QPixmap* add_mode_pixmap;

        switch(tower_code){
        case NORMAL:
            build.push_back(new Tower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_Assistant.bmp")); break;
        case SPLASH:
            build.push_back(new SplashTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_Mechanical.bmp"));break;
        case SLOW:
            build.push_back(new SlowTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_SMP.bmp"));break;
        case POISON:
            build.push_back(new PoisonTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_Chemical.bmp"));break;
        case CHAIN:
            build.push_back(new ChainTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_Electronic.bmp"));break;
        case GOLD:
            build.push_back(new GoldTower());
            add_mode_pixmap = new QPixmap(QString(":/images/Icon_IME.bmp"));break;
        }

        QCursor* add_mode_cursor = new QCursor(*add_mode_pixmap);
        QWidget::unsetCursor();
        QWidget::setCursor(*add_mode_cursor);

        control->ADD(build[build.size()-1]);

        build[build.size()-1]->SetAttackPower(upgrade_button->getUp()->GetReference(tower_code)->GetAttackPower());
        build[build.size()-1]->SetDefensivePower(upgrade_button->getUp()->GetReference(tower_code)->GetDefensivePower());
        build[build.size()-1]->SetAttackSpeed(upgrade_button->getUp()->GetReference(tower_code)->GetAttackSpeed());

    }

    //when start button pressed.
    else if(start_pause_button->contains(point) == true && state == Cleared){

        for(int i=0 ; i<build.size() ; i++){
            build[i]->Activated(true);
        }

        MakeNewGame();

        spawn_timer = new QTimer(this);
        connect(spawn_timer,SIGNAL(timeout()),this,SLOT(spawnEnemy()));
        spawn_timer->start(1000);

        state = Ingame;
    }

    else if(start_pause_button->contains(point)==true && state == GameOver){

        set_money(0);
        wave = 0;
        dead_enemy=0;
        enemy_num=0;

        for(int i=0 ; i<build.size() ; i++){

            switch(build[i]->GetTowerCode()){
            case NORMAL:
                set_money(get_money() + 20);break;
            case SPLASH:
                set_money(get_money() + 30);break;
            case SLOW:
                set_money(get_money() + 30);break;
            case POISON:
                set_money(get_money() + 35);break;
            case CHAIN:
                set_money(get_money() + 40);break;
            case GOLD:
                set_money(get_money() + 60);break;
            case TUTOR:
                set_money(get_money() + 70);break;
            case PROF:
                set_money(get_money() + 50);break;
            case CES:
                set_money(get_money() + 95);break;
            case JOBSBIO:
                set_money(get_money() + 100);break;
            case MES:
                set_money(get_money() + 90);break;
            case APPLE:
                set_money(get_money() + 170);break;
            case JOBS:
                set_money(get_money() + 150);break;
            case TRIPLE:
                set_money(get_money() + 185);break;
            }
            set_money(get_money() +
                      (upgrade_button->getUp()->GetReference(build[i]->GetTowerCode())->GetDefensivePower()-20)/10*15);
        }
        for(int i=0 ; i<build.size() ; i++){
            control->Delete(build[i]);
            build[i]->DelHpBar();
            delete build[i];
        }

        for(int i=0 ; i<SpawnList.size() ; i++){
            control->Delete(SpawnList[i]);
            delete SpawnList[i];
        }
        SpawnList.clear();

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

        SetLife(100);
        hpBar->setRect(0,0, (704-256)*((float(life)/100)), float(42-21));
        scene->addItem(hpBar);
        state = Cleared;
        delete game_over;
    }
}

//method to clear game
//this method is called when all spawned enemies is removed from scene
void Game::clear_game()
{    
    wave_generator.ClearSpwanList();

    set_round(get_round() + 1);
    set_money(get_money() + dead_enemy*5);
    hpBar->setRect(0,0, (704-256)*((float(life)/100)), float(42-21));

    wave = 0;
    dead_enemy=0;
    enemy_num=0;

    for(int i=0 ; i<build.size() ; i++){
        build[i]->Activated(false);
    }
}


//method to show an selected tower information
//this method is called when an user selected an tower in map.
void Game::ShowTowerInfo(Tower *tower)
{
    if(tooltip && movie_tooltip && attack_ability && defense_ability && attack_speed_ability && widget_tooltip && widget_atk && widget_atkspd && widget_def){
        scene->removeItem(widget_tooltip);
        scene->removeItem(widget_atk);
        scene->removeItem(widget_atkspd);
        scene->removeItem(widget_def);


        //delete tooltip;
        delete widget_tooltip;
        tooltip = nullptr;

        delete movie_tooltip;
        movie_tooltip = nullptr;

        //delete attack_ability;
        delete widget_atk;
        attack_ability = nullptr;

        //delete defense_ability;
        delete widget_def;
        defense_ability = nullptr;

        //delete attack_speed_ability;
        delete widget_atkspd;
        attack_speed_ability = nullptr;
        //qDebug()<<"Entered InfoLabelDeleting";

        widget_tooltip = nullptr;
        widget_atk = nullptr;
        widget_atkspd = nullptr;
        widget_def = nullptr;
    }
    tooltip = new QLabel();
    tooltip->setGeometry(768,384,256,192);

    int towerType = tower->GetTowerCode();
    switch(towerType){

    case NORMAL:
        movie_tooltip = new QMovie(":/images/FieldTooltip_Assistant.gif");break;
    case SPLASH:
        movie_tooltip = new QMovie(":/images/FieldTooltip_Mechanical.gif");break;
    case SLOW:
        movie_tooltip = new QMovie(":/images/FieldTooltip_SMP.gif");break;
    case POISON:
        movie_tooltip = new QMovie(":/images/FieldTooltip_Chemical.gif");break;
    case CHAIN:
        movie_tooltip = new QMovie(":/images/FieldTooltip_Electronics.gif");break;
    case GOLD:
        movie_tooltip = new QMovie(":/images/FieldTooltip_IME.gif");break;
    case TUTOR:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV2_TutoringMachine.gif");break;
    case PROF:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV2_Session.gif");break;
    case CES:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV2_ChemEng.gif");break;
    case MES:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV2_Metal.gif");break;
    case JOBSBIO:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV2_JobsBook.gif");break;
    case APPLE:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV3_AppleDeathMachinel.gif");break;
    case JOBS:
        movie_tooltip = new QMovie(":/images/FieldTooltipLV3_JobsDream.gif");break;
    case TRIPLE:
        movie_tooltip = new QMovie(":/FieldTooltipLV3_3Major.gif");break;
    }
    tooltip->setMovie(movie_tooltip);
    tooltip->movie()->start();
    widget_tooltip = scene->addWidget(tooltip);

    char buff[100];

    int id = QFontDatabase::addApplicationFont(":/fonts/PressStart2P.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont mystyle(family);
    mystyle.setPointSize(100);
    mystyle.setPointSize(6);

    sprintf(buff, "%d", tower->GetAttackPower());
    attack_ability = new QLabel(QString("ATK: ")+QString(buff));
    attack_ability->setFont(mystyle);
    attack_ability->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : black; }");
    attack_ability->setGeometry(1024-32*5.4,32*12.3,512,80);
    widget_atk = scene->addWidget(attack_ability);

    sprintf(buff, "%d", tower->GetDefensivePower());
    defense_ability = new QLabel(QString("DEF: ")+QString(buff));
    defense_ability->setFont(mystyle);
    defense_ability->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : black; }");
    defense_ability->setGeometry(1024-32*3,32*12.8,512,80);
    widget_def = scene->addWidget(defense_ability);

    sprintf(buff, "%d", tower->GetAttackSpeed());
    attack_speed_ability = new QLabel(QString("SPD: ")+QString(buff));
    attack_speed_ability->setFont(mystyle);
    attack_speed_ability->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : black; }");
    attack_speed_ability->setGeometry(1024-32*5.4,32*12.8,512,80);
    widget_atkspd = scene->addWidget(attack_speed_ability);

}


//method to hide tower information
//this method is called when we have to hide information of tower
void Game::DeletTowerInfo()
{
    if(tooltip && movie_tooltip && attack_ability && defense_ability && attack_speed_ability && widget_tooltip && widget_atk && widget_atkspd && widget_def){
        scene->removeItem(widget_tooltip);
        scene->removeItem(widget_atk);
        scene->removeItem(widget_atkspd);
        scene->removeItem(widget_def);


        //delete tooltip;
        delete widget_tooltip;
        tooltip = nullptr;

        delete movie_tooltip;
        movie_tooltip = nullptr;

        //delete attack_ability;
        delete widget_atk;
        attack_ability = nullptr;

        //delete defense_ability;
        delete widget_def;
        defense_ability = nullptr;

        //delete attack_speed_ability;
        delete widget_atkspd;
        attack_speed_ability = nullptr;
        //qDebug()<<"Entered InfoLabelDeleting";

        widget_tooltip = nullptr;
        widget_atk = nullptr;
        widget_atkspd = nullptr;
        widget_def = nullptr;
    }
}

void Game::CheatKeyEntered()
{
    QStringList input = textBox->text().split(" ");
    if(input.size() == 2 && input.at(0) == QString("round") && input.at(1).toInt() > 0 && input.at(1).toInt() < 50){
        set_round(input.at(1).toInt()-1);
        this->SetState(Cleared);
        textBox->setText(QString(""));
    }

    if(textBox->text() == QString("show me the money")){
        set_money(99999);
        textBox->setText(QString(""));
    }
    else
        textBox->setText(QString(""));
}

void Game::destroy_game()
{
    int id = QFontDatabase::addApplicationFont(":/fonts/PressStart2P.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont mystyle(family);

    game_over = new QLabel("GAME OVER!");
    mystyle.setBold(true);
    mystyle.setPointSize(40);
    game_over->setFont(mystyle);
    game_over->setGeometry(1024/8,768/3,512,80);
    game_over->setStyleSheet("QLabel { background-color : rgba(0,0,0,0%); color : black; }");
    scene->addWidget(game_over);

    wave_generator.ClearSpwanList();
    wave = 0;
    dead_enemy=0;
    enemy_num=0;
}

void Game::change()
{
    if(upgrade_mode == true){
        upgrade_button->setPixmap(QPixmap(":/images/UpgradeButton.bmp"));
        this->scene->addItem(upgrade_button);
        upgrade_mode = false;
    }
    if(fuse_mode == true){
        fusion_button->setPixmap(QPixmap(":/images/FusionButton.bmp"));
        this->scene->addItem(fusion_button);
        fuse_mode = false;
    }
    else{
        start_pause_button->setPixmap(QPixmap(":/images/StartButton.bmp"));
        this->scene->addItem(start_pause_button);
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
        pointer->setHpbar();
        scene->addItem(pointer);
        QWidget::unsetCursor();

        this->position[pointed_spot.x()/64][pointed_spot.y()/64] = true;
        add_mode = false;
        money_label->setText(QString::number(money));
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


//method to renew the number of enemies which are still in map
//when the number of enemies in the map goes to zero, we change state of game to CLERED
void Game::RenewEnemyNum(bool is_dead)
{
    enemy_num--;

    if(is_dead)
        dead_enemy++;

    if(wave == SpawnList.size() && enemy_num == 0 && state != GameOver){
        SetState(Cleared);
    }
}


//method to make new game when new round of game begins
//we clean enemy & spawn list, renew level and money, and generate new waves.
void Game::MakeNewGame()
{
    for(int i=0 ; i<SpawnList.size() ; i++){
        control->Delete(SpawnList[i]);
        delete SpawnList[i];
    }
    enemy.clear();
    SpawnList.clear();
    SpawnList = wave_generator.MakeSpawnList(get_round());
}

bool Game::FuseTower()
{
    if(waiting_line.size() == 2){

        Tower* new_tower;
        int first = waiting_line[0]->GetTowerCode();
        int second = waiting_line[1]->GetTowerCode();

        if(combination[first][second] == true){
            new_tower = waiting_line[0]->fuseTower(waiting_line[0],waiting_line[1]);

            control->Delete(waiting_line[0]);
            control->Delete(waiting_line[1]);
            scene->removeItem(waiting_line[0]);
            scene->removeItem(waiting_line[1]);

            build.erase(std::find(build.begin(),build.end(),waiting_line[0]));
            build.erase(std::find(build.begin(),build.end(),waiting_line[1]));

            position[static_cast<int>(waiting_line[0]->pos().x()/64)][static_cast<int>(waiting_line[0]->pos().y()/64)] = false;
            position[static_cast<int>(waiting_line[1]->pos().x()/64)][static_cast<int>(waiting_line[1]->pos().y()/64)] = false;

            waiting_line[0]->DelHpBar();
            waiting_line[1]->DelHpBar();

            delete waiting_line[0];
            delete waiting_line[1];
            waiting_line.clear();

            build.push_back(new_tower);
            control->ADD(new_tower);
            add_mode = true;
            QPixmap* pixmap;

            switch(new_tower->GetTowerCode()){
            case TUTOR:
                pixmap = new QPixmap(QString(":/images/IconLV2_TutorRobot.bmp"));break;
            case PROF:
                pixmap = new QPixmap(QString(":/images/IconLV2_Session.bmp"));break;
            case CES:
                pixmap = new QPixmap(QString(":/images/IconLV2_ChemEng.bmp"));break;
            case MES:
                pixmap = new QPixmap(QString(":/images/IconLV2_Metal.bmp"));break;
            case JOBSBIO:
                pixmap = new QPixmap(QString(":/images/IconLV2_JobsBook.bmp"));break;
            case APPLE:
                pixmap = new QPixmap(QString(":/images/IconLV3_AppleDeathMachine.bmp"));break;
            case JOBS:
                pixmap = new QPixmap(QString(":/images/IconLV3_JobsDream.bmp"));break;
            case TRIPLE:
                pixmap = new QPixmap(QString(":/images/IconLV3_3Major.bmp"));break;
            }

            QCursor* new_cursor = new QCursor(*pixmap);
            QWidget::unsetCursor();
            QWidget::setCursor(*new_cursor);

            delete attack_ability;
            attack_ability = nullptr;

            delete defense_ability;
            defense_ability = nullptr;

            delete attack_speed_ability;
            attack_speed_ability = nullptr;

            return true;
        }
        else return false;
    }
    else return false;
}

void Game::DestroyTower(Tower * target)
{
    QVector<Tower*>::iterator pos = std::find(build.begin() , build.end() ,target);
    if(pos != build.end()){
        build.erase(pos);
        position[static_cast<int>(target->pos().x()/64)][static_cast<int>(target->pos().y()/64)] = false;
        control->Delete(target);
        delete target;
    }
}

//method to modify state of the game
//this mehod emit signal that all enemies are removed from the scene
void Game::SetState(int _state){
    state = _state;

    if(_state == GameOver){
        emit game_is_over();
    }

    else if(_state == Cleared){
        emit game_is_cleared();
    }
}

int Game::GetState()
{
    return state;
}

void Game::SetLife(int _life)
{
    if(life >0){
        life = _life;
        if(life <= 0)
            SetState(GameOver);

        hpBar->setRect(0,0, (704-256)*((float(life)/100)), float(42-21));
    }
    if(state == GameOver)
        life = _life;
}

void Game::set_money(int _money){
    money = _money;
    money_label->setText(QString::number(money));
}

void Game::set_round(int _round)
{
    if(round != _round){
        round = _round;
        round_label->setText(QString("Round ")+QString::number(round));
    }
}

