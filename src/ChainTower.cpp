#include "ChainTower.h"

ChainTower::ChainTower()
{
    TargetNum = 3;
    TowerCode = CHAIN;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //사진설정
}

void ChainTower::SetTarget()
{
    int attack_num=0;                          //세개의 타겟에 대해서 공격가능하므로 세번까지 가능
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange와 colliding하는 item들
    for(size_t j = 0, m = colliding_items.size();j<m;j++){              //부딪히는 아이템들 다 검사
        if(typeid(*(colliding_items[j]))==typeid(Enemy))                   //Enemy가 있으면
            break;                                                         //중지하고 밑에 바로 실행
        else if(j == m-1){                                                 //없으면
            HasTarget = false;
            return;                                                        //리턴
        }
    }
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test&&attack_num<3){                          //enemy일 경우만
            Target = test;
            HasTarget = true;                  //가장가까운 적이 Target이 되도록함
            Attack();
            playSound("BulletWentOff");
            attack_num++;
        }
    }
}

