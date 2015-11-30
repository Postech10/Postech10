#include "TutorRobot.h"

TutorRobot::TutorRobot()
{
    TargetNum = 3;
    TowerCode = TUTOR;
    Hp = 100;
    AttackPower = 30;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //set pic
}

void TutorRobot::SetTarget()
{
    int attack_num=0;                          //target max num = 3
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();// items collides with attack range
    for(size_t j = 0, m = colliding_items.size();j<m;j++){
        if(typeid(*(colliding_items[j]))==typeid(Enemy))                   //if enemy
            break;
        else if(j == m-1){                                                 //no enemy
            HasTarget = false;
            return;                                                        //return
        }
    }
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test&&attack_num<3){                          //only for enemy and smaller than MAX target num
            Target = test;
            HasTarget = true;
            Attack();
            playSound("BulletWentOff");
            attack_num++;
        }
    }
}

