#ifndef PROFESSORMEETING_H
#define PROFESSORMEETING_H

#include "SlowTower.h"
#include "PMBullet.h"

//this tower from Slow + Normal

class ProfessorMeeting: public SlowTower{
public:
    ProfessorMeeting();
    void Attack();
};

#endif // PROFESSORMEETING_H
