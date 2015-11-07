#include "Tower.h"

Tower::Tower()
{
    TargetNum = 1;
    TowerCode = NORMAL;
}

void Tower::upgrade(Upgrades up, int towercode)
{
    this->SetAttackPower(up.GetReference(towercode).GetAttackPower());
    this->SetDefensivePower(up.GetReference(towercode).GetDefensivePower());
    this->SetAttackSpeed(up.GetReference(towercode).GetAttackSpeed());
}
