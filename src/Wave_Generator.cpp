#include "Wave_Generator.h"
#include <qdebug.h>

WaveGenerator::WaveGenerator()
{

}

QVector<Enemy *> WaveGenerator::MakeSpawnList(int round)
{
    if(round <10){
        for(int i=0 ; i<7*round ; i++){
            SpawnList.push_back(new Enemy(round));
        }
    }

    else if(round == 10){
        SpawnList.push_back(new AttackableEnemy(round));
    }

    else if(round >10 && round <20){
        for(int i=0 ; i<7*(round-10) ; i++){
            SpawnList.push_back(new Enemy(round));
            SpawnList.push_back(new Enemy(round-10));
        }
    }

    else if(round == 20)
        SpawnList.push_back(new AttackableEnemy(round));

    else if(round > 20 && round <30){
        for(int i=0 ; i<7*(round-20) ; i++){
            SpawnList.push_back(new Enemy(round));
            SpawnList.push_back(new Enemy(round-20));
            SpawnList.push_back(new Enemy(round-10));
        }
    }
    else if(round == 30){
        SpawnList.push_back(new AttackableEnemy(round));
    }
    else if(round > 30 && round <40){
          for(int i=0 ; i<7*(round-30) ; i++){
              SpawnList.push_back(new Enemy(round));
              SpawnList.push_back(new Enemy(round-10));
              SpawnList.push_back(new Enemy(round-20));
              SpawnList.push_back(new Enemy(round-30));
          }
    }
    else if(round == 40){
        SpawnList.push_back(new AttackableEnemy(round));
    }

    return SpawnList;
}

void WaveGenerator::ClearSpwanList()
{    
    SpawnList.clear();
}
