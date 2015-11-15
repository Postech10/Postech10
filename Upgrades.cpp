#include "Upgrades.h"

#define DEFAULT_UPGRADE_AMOUNT 10

Tower* Upgrades::GetReference(int towercode)//return type shoud be a pointer
{
    switch(towercode){
    case NORMAL:
        return &normalref;
    case SPLASH:
        return &splashref;
    case SLOW:
        return &slowref;
    case POISON:
        return &poisonref;
    case CHAIN:
        return &chainref;
    case GOLD:
        return &goldref;
    case TUTOR:
        return &tutref;
    case PROF:
        return &profref;
    case CES:
        return &cesref;
    case JOBSBIO:
        return &jobsbioref;
    case MES:
        return &mesref;
    case APPLE:
        return &appleref;
    case JOBS:
        return &jobsref;
    case TRIPLE:
        return &tripleref;
    }
}

void Upgrades::UpgradeAttack(int towercode)
{
    Tower *ref = GetReference(towercode);
    ref->SetAttackPower(ref->GetAttackPower()+DEFAULT_UPGRADE_AMOUNT);
}

void Upgrades::UpgradeDefense(int towercode)
{
    Tower *ref = GetReference(towercode);
    ref->SetDefensivePower(ref->GetDefensivePower()+DEFAULT_UPGRADE_AMOUNT);
}

void Upgrades::UpgradeSlow(int towercode)
{
    Tower *ref = GetReference(towercode);//should get a Tower Pointer
    ref = dynamic_cast<SlowTower*>(ref);
    dynamic_cast<SlowTower*>(ref)->SetSlowPower(dynamic_cast<SlowTower*>(ref)->GetSlowPower()+DEFAULT_UPGRADE_AMOUNT);
}

void Upgrades::UpgradeGold(int towercode)
{
    Tower *ref = GetReference(towercode);//should get a Tower pointer
    dynamic_cast<GoldTower*>(ref)->SetGoldPower(dynamic_cast<GoldTower*>(ref)->GetGoldPower()+DEFAULT_UPGRADE_AMOUNT);
}

void Upgrades::UpgradeAttackSpeed(int towercode)
{
    Tower *ref = GetReference(towercode);
    ref->SetAttackSpeed(ref->GetAttackSpeed()+DEFAULT_UPGRADE_AMOUNT);
}

