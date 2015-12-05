#include "ChainTower.h"

ChainTower::ChainTower()
{
    TargetNum = 3;
    TowerCode = CHAIN;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //this will be changed for balance
    set_image(QString::fromStdString("://images/Animation_Electronic.bmp"));
    set_state(CALM);
}

void ChainTower::SetTarget()
{
    int attack_num=0;                          //target max num = 3
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange's colliding item
    for(size_t j = 0, m = colliding_items.size();j<m;j++){
        if((typeid(*(colliding_items[j]))==typeid(Enemy))||typeid(*(colliding_items[j]))==typeid(AttackableEnemy))     //if Enemy
            break;
        else if(j == m-1){                                                 //no enemy
            HasTarget = false;
            return;                                                        //return
        }
    }
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test;
        if(typeid(*(colliding_items[i]))==typeid(Enemy))
            test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        else if(typeid(*(colliding_items[i]))==typeid(AttackableEnemy))
            test = dynamic_cast<AttackableEnemy *>(colliding_items[i]);
        else
            continue;
        if(attack_num<3){                          //only for enemy and smaller than MAX target num
            Target = test;
            HasTarget = true;
            Attack();
            playSound("BulletWentOff");
            attack_num++;
        }
    }
}

