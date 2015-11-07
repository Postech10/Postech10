#ifndef UPGRADES
#define UPGRADES

#include "Tower.h"

class Upgrades{
public:
    Tower GetReference(int towercode);
    void UpgradeAttack(int towercode);
    void UpgradeDefense(int towercode);
    void UpgradeSlow(int towercode);                    //나중에
    void UpgradeGold(int towercode);
    void UpgradeAttackSpeed(int towercode);
private:
    Tower normalref;
    SplashTower splashref;
    SlowTower slowref;
    PoisonTower poisonref;
    ChainTower chainref;
    GoldTower goldref;
    TutorRobot tutref;
    ProfessorMeeting profref;
    ChemEngSenior cesref;
    JobsBiography jobsbioref;
    MetalEngSeniot mesref;
    AppleRobot appleref;
    SteveJobs jobsref;
    TripleMajorSenior tripleref;
};

#endif // UPGRADES

