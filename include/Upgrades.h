#ifndef UPGRADES
#define UPGRADES

#include "PoisonTower.h"
#include "ChainTower.h"
#include "TutorRobot.h"
#include "ProfessorMeeting.h"
#include "ChemEngSenior.h"
#include "AppleRobot.h"
#include "SteveJobs.h"
#include "TripleMajorSenior.h"

class Upgrades{
public:
    Tower* GetReference(int towercode);
    void UpgradeAttack(int towercode);
    void UpgradeDefense(int towercode);
    void UpgradeSlow(int towercode);
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
    MetalEngSenior mesref;
    AppleRobot appleref;
    SteveJobs jobsref;
    TripleMajorSenior tripleref;
};

#endif // UPGRADES

