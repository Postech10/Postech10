#include "Tower.h"
#include "Upgrades.h"
#include "Game.h"

#include <qdebug.h>

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
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString(":/images/Animation_Assistant.bmp"));
    set_state(CALM);
}

void Tower::upgrade(Upgrades* up, int towercode)
{
    //upgrade proceed
        up->UpgradeAttack(towercode);
        up->UpgradeDefense(towercode);
        //up->UpgradeAttackSpeed(towercode);
        switch(towercode)
        {
        case NORMAL:
            break;
        case SPLASH:
            break;
        case SLOW:
            up->UpgradeSlow(towercode);
            break;
        case POISON:
            break;
        case CHAIN:
            break;
        case GOLD:
            up->UpgradeGold(towercode);
            break;
        case TUTOR:
            break;
        case PROF:
            up->UpgradeSlow(towercode);
            break;
        case CES:
            up->UpgradeGold(towercode);
            break;
        case JOBSBIO:
            up->UpgradeGold(towercode);
            break;
        case MES:
            up->UpgradeGold(towercode);
            break;
        case APPLE:
            up->UpgradeGold(towercode);
            break;
        case JOBS:
            break;
        case TRIPLE:
            up->UpgradeGold(towercode);
            break;
        }


    this->SetAttackPower(up->GetReference(towercode)->GetAttackPower());
    this->SetDefensivePower(up->GetReference(towercode)->GetDefensivePower());
    this->SetAttackSpeed(up->GetReference(towercode)->GetAttackSpeed());
}

Tower* Tower::fuseTower(Tower *tow1, Tower *tow2)
{
    /*타워 조합 공식
     * @@1+1=2@@
     * NORMAL + SLOW = PROF 0*2 = 0
     * SPLASH + CHAIN = TUTOR 1*4 = 4
     * SPLASH + GOLD = MES 1*5 = 5
     * POISON + GOLD = CES 3*5 = 15
     * CHAIN + GOLD = JOBSBIO 4*5 = 20
     *
     * @@2+2=3@@
     * TUTOR + JOBSBIO = APPLE 6*9 = 54
     * PROF + JOBSBIO = JOBS 7*9 = 63
     * CES + MES = TRIPLE 8*10=80*/
    //requirement : tow1, tow2 should be possible combination number
    //if inputs are wrong with above manual, it would produce error
    int mult_code = tow1->GetTowerCode()*tow2->GetTowerCode();

    switch(mult_code){
    case 0:
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
        return new TripleMajorSenior();     //return proper tower
    }
}

int Tower::GetTargetNum()
{
    return TargetNum;
}

int Tower::GetTowerCode()
{
    return TowerCode;
}

void Tower::IsHitBy(int AttackPower)
{
    Hp = Hp - AttackPower/DefensivePower;       //not perfect equation yet

    if(Hp<=0){
        scene()->removeItem(hpBar);
        scene()->removeItem(this);
        game->DestroyTower(this);
    }
    else
        cutHpbar();
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(choose == false && game->GetAddMode()==false){
        if(game->waiting_line.size() < 2){
           AttackRange->setPen(QPen(QBrush(Qt::red),3));
           choose = true;
           game->waiting_line.push_back(this);
           game->ShowTowerInfo(this);
           playSound("TowerSelected");
        }
        else playSound("TowerSelectFail");
    }

    else if(choose == true){
      AttackRange->setPen(QPen(Qt::DotLine));
        choose = false;
        game->waiting_line.removeOne(this);
        game->DeletTowerInfo();
        playSound("TowerSelected");
    }
}
