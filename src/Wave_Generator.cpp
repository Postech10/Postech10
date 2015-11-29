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
        SpawnList.push_back(new (議곗썝???ы븰?앹씠 ?놁뼱 遺덈쭔???숈깮));
    }

    else if(round >10 && round <20){
        for(int i=0 ; i<?대뼡 ?レ옄 ; i++){
            SpawnList.push_back(new (議몄뾽?숆린??而닿났怨??숈깮));
        }
    }
    else if(round == 20)
        SpawnList.push_back(new (援고쑕?묒쓣 寃곗젙??而닿났怨??숈깮));

    else if(round > 20 && round <30){
        for(int i=0 ; i<?대뼡 ?レ옄 ; i++){
            SpawnList.push_back(new (而닿났怨?蹂듭닔 ?꾧났&遺??);
        }
    }
    else if(round == 30){
        SpawnList.push_back(new (議곗썝 3紐낆씠 ?섍컯?ш린???숈깮));
    }
    else if(round > 30 && round <40){
        for(int i=0 ; i<?대뼡 ?レ옄 ; i++){
            SpawnList.push_back(new (鍮꾩뺨怨듦낵 ?숈깮));
        }
    }
    else if(round == 40){
        SpawnList.push_back(new (?먮떎媛 ?쒗뿕 紐삳낯 ?숈깮));
    }
    */

    return SpawnList;
}

void WaveGenerator::ClearSpwanList(int wave)
{
    SpawnList.clear();
}
