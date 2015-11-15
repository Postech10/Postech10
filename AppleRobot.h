#ifndef APPLEROBOT_H
#define APPLEROBOT_H

#include "JobsBiography.h"
#include "SplashLaser.h"

class AppleRobot: public JobsBiography{

public:
    AppleRobot();
    void Attack();
};

#endif // APPLEROBOT_H
