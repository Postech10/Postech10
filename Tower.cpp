#include "Tower.h"
#include "Upgrades.h"

Tower::Tower()
{
    TargetNum = 1;
    TowerCode = NORMAL;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    setPixmap(QPixmap(":/images/Tower.png"));     //사진설정

}

void Tower::upgrade(Upgrades up, int towercode)
{
    this->SetAttackPower(up.GetReference(towercode)->GetAttackPower());
    this->SetDefensivePower(up.GetReference(towercode)->GetDefensivePower());
    this->SetAttackSpeed(up.GetReference(towercode)->GetAttackSpeed());
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
    delete tow1;
    delete tow2;                    //재료가 되는 두 타워는 지움
    switch(mult_code){
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
}

int Tower::GetTowerCode()
{
    return TowerCode;
}
