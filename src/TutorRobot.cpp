#include "TutorRobot.h"

TutorRobot::TutorRobot()
{
    TargetNum = 3;
    TowerCode = TUTOR;
    Hp = 100;
    AttackPower = 30;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //珥덇린?ㅼ젙 ?섏쨷??諛몃윴?ㅻ? ?꾪빐 諛붽?嫄곗엫
    setPixmap(QPixmap(":/images/Mechanical.bmp"));     //?ъ쭊?ㅼ젙
}

void TutorRobot::SetTarget()
{
    int attack_num=0;                          //?멸컻???寃잛뿉 ??댁꽌 怨듦꺽媛?ν븯誘濡??몃쾲源뚯? 媛??
    QList<QGraphicsItem *> colliding_items= AttackRange->collidingItems();//AttackRange? colliding?섎뒗 item??
    for(size_t j = 0, m = colliding_items.size();j<m;j++){              //遺?ろ엳???꾩씠?쒕뱾 ??寃??
        if(typeid(*(colliding_items[j]))==typeid(Enemy))                   //Enemy媛 ?덉쑝硫?
            break;                                                         //以묒??섍퀬 諛묒뿉 諛붾줈 ?ㅽ뻾
        else if(j == m-1){                                                 //?놁쑝硫?
            HasTarget = false;
            return;                                                        //由ы꽩
        }
    }
    for (size_t i=0, n=colliding_items.size();i<n;i++){
        Enemy *test = dynamic_cast<Enemy *>(colliding_items[i]);           //colliding enemy
        if(test&&attack_num<3){                          //enemy??寃쎌슦留?
            Target = test;
            HasTarget = true;                  //媛?κ?源뚯슫 ?곸씠 Target???섎룄濡앺븿
            Attack();
            playSound("BulletWentOff");
            attack_num++;
        }
    }
}

