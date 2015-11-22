#ifndef TUTORROBOT_H
#define TUTORROBOT_H

#include "SplashTower.h"

class TutorRobot: public SplashTower{
public:
    TutorRobot();
public slots:
    void SetTarget();
};

#endif // TUTORROBOT_H
