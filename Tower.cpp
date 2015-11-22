#include "Tower.h"
#include <QVector>
#include <QPointF>
#include "Upgrades.h"
#include "Game.h"
#include <QDebug>

extern Game* game;

Tower::Tower()
{
    TargetNum = 1;
    TowerCode = NORMAL;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    choose = false;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //사진설정

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(SetTarget()));
    timer->start(2500);
}

void Tower::upgrade(Upgrades* up, int towercode)
{
    this->SetAttackPower(up->GetReference(towercode)->GetAttackPower());
    this->SetDefensivePower(up->GetReference(towercode)->GetDefensivePower());
    this->SetAttackSpeed(up->GetReference(towercode)->GetAttackSpeed());
}

Tower* Tower::fuseTower(Tower *tow1, Tower *tow2)
{
    /*타워 조합 공식
     * @@1+1=2@@
     * NORMAL + SLOW = PROF 0*2 = 2
     * SPLASH + CHAIN = TUTOR 1*4 = 4
     * SPLASH + GOLD = MES 1*5 = 5
     * POISON + GOLD = CES 3*5 = 15
     * CHAIN + GOLD = JOBSBIO 4*5 = 20
     *
     * @@2+2=3@@
     * TUTOR + JOBSBIO = APPLE 6*9 = 54
     * PROF + JOBSBIO = JOBS 7*9 = 63
     * CES + MES = TRIPLE 8*10=80*/
    //필수사항 : 만드시 조합가능한거 끼리만 이 함수에 들어올수 있도록 해야함, 아니면 조합이
    //안되는 두가지 임에도 불구하고 조합이 되어 나갈수도 있음!!
    int mult_code = tow1->GetTowerCode()*tow2->GetTowerCode();

/*
    delete tow1;
    delete tow2;                    //재료가 되는 두 타워는 지움*/

    //지우기 전에 game class에서 처리할 것이 있기 때문에
    //game class에서 지우는 걸

    switch(mult_code){
    case 0:                       //디버깅용
        return new AppleRobot();       //디버깅용
    case 2:
        return new ProfessorMeeting();
    case 4:
        return new TutorRobot();
    case 5:
        return new MetalEngSenior();
    case 15:
        return new ChemEngSenior();
    case 20:
        return new JobsBiography();
    case 54:
        return new AppleRobot();
    case 63:
        return new SteveJobs();
    case 80:
        return new TripleMajorSenior();     //조합에 따라 알맞은 타워 반환
    }
}

int Tower::GetTargetNum()
{
    return TargetNum;
/*=======hw used this method for "Maximum Targets"
 * HOWEVER, Sangjin used this for scanning enemies(?) if i'm right.
 * you two are on mission to solve this
 * ---------------------------------------------------------
    if(choose == false && game->GetAddMode()==false){
        if(game->waiting_line.size() < 2){
           attack_area->setPen(QPen(Qt::SolidLine));
           choose = true;
           game->waiting_line.push_back(this);
        }
    }

    else if(choose == true){
      attack_area->setPen(QPen(Qt::DotLine));
        choose = false;
        if(game->waiting_line[0] == this)
            game->waiting_line.remove(0);
        else
           game->waiting_line.remove(1);
    }        
>>>>>>> game*/
}

int Tower::GetTowerCode()
{
    return TowerCode;
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(choose == false && game->GetAddMode()==false){
        if(game->waiting_line.size() < 2){
           AttackRange->setPen(QPen(QBrush(Qt::red),3));
           choose = true;
           game->waiting_line.push_back(this);
           game->ShowTowerInfo(this);
        }
    }

    else if(choose == true){
      AttackRange->setPen(QPen(Qt::DotLine));
        choose = false;
        game->waiting_line.removeOne(this);
        game->DeletTowerInfo();
    }
}
