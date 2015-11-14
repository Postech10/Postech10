#ifndef PMBULLET_H
#define PMBULLET_H

#include "SlowBullet.h"

class PMBullet: public SlowBullet{
public:
    PMBullet(int,int);
public slots:
    void move();
};

#endif // PMBULLET_H
