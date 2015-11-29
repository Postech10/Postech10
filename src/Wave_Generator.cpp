#include "Wave_Generator.h"
#include <qdebug.h>

WaveGenerator::WaveGenerator()
{

}

QVector<Enemy *> WaveGenerator::MakeSpawnList(int round)
{
    if(round <10){
        for(int i=0 ; i<5*round ; i++){
            SpawnList.push_back(new(Enemy));
        }
    }
/*
    else if(round == 10){
        SpawnList.push_back(new (조원에 여학생이 없어 불만인 학생));
    }

    else if(round >10 && round <20){
        for(int i=0 ; i<어떤 숫자 ; i++){
            SpawnList.push_back(new (졸업학기인 컴공과 학생));
        }
    }
    else if(round == 20)
        SpawnList.push_back(new (군휴햑을 결정한 컴공과 학생));

    else if(round > 20 && round <30){
        for(int i=0 ; i<어떤 숫자 ; i++){
            SpawnList.push_back(new (컴공과 복수 전공&부전));
        }
    }
    else if(round == 30){
        SpawnList.push_back(new (조원 3명이 수강포기한 학생));
    }
    else if(round > 30 && round <40){
        for(int i=0 ; i<어떤 숫자 ; i++){
            SpawnList.push_back(new (비컴공과 학생));
        }
    }
    else if(round == 40){
        SpawnList.push_back(new (자다가 시험 못본 학생));
    }
    */

    return SpawnList;
}

void WaveGenerator::ClearSpwanList(int wave)
{
    SpawnList.clear();
}
