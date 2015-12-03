#pragma once
#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

#include "enemy.h"
#include "attackableenemy.h"
#include <QVector>


class WaveGenerator
{
public:
    WaveGenerator();
    QVector<Enemy *> MakeSpawnList(int round);
    void ClearSpwanList();

signals:

public slots:
    QVector<Enemy*> SpawnList;
};

#endif // WAVEGENERATOR_H
