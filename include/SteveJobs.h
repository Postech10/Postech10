﻿#ifndef STEVEJOBS_H
#define STEVEJOBS_H

#include "Tower.h"

class SteveJobs: public Tower{
    Q_OBJECT
public:
    SteveJobs();
    void Activated(bool);
public slots:
    void IncGold();
};

#endif // STEVEJOBS_H
