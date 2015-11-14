#include "Tower.h"

Tower::Tower()
{
<<<<<<< HEAD
<<<<<<< HEAD
    setPixmap(QPixmap(":/images/Machanical.bmp"));     //사진설정

    QVector<QPointF> points;
    points << QPoint(1,0)<< QPoint(2,0)<< QPoint(3,1)<< QPoint(3,2)<< QPoint(2,3)
              << QPoint(1,3)<< QPoint(0,2)<< QPoint(0,1);
    int SCALE_FACTOR = 80;                          //범위 설정
    for (size_t i=0, n=points.size(); i<n;i++)
        points[i]*=SCALE_FACTOR;                    //확대

    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);
    attack_area->setPen(QPen(Qt::DotLine));     //점선으로 범위 보이기

    QPointF poly_center(1.5,1.5);
    poly_center *= SCALE_FACTOR;                //역시 확대
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+50, y()+65);
    QLineF ln(poly_center, tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());       //center 맞추기

    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(aquire_target()));
    timer->start(2500);
    attack_dest = QPointF(800,0);

    choose = false;
=======
=======
>>>>>>> BattleObject-&-Tower
    TargetNum = 1;
    TowerCode = NORMAL;
    Hp = 100;
    AttackPower = 20;
    DefensivePower = 20;
    AttackSpeed = 20;
    Attackable = true;                  //초기설정 나중에 밸런스를 위해 바꿀거임
<<<<<<< HEAD
>>>>>>> origin/BattleObject-&-Tower
=======
>>>>>>> BattleObject-&-Tower
}

void Tower::upgrade(Upgrades up, int towercode)
{
    this->SetAttackPower(up.GetReference(towercode).GetAttackPower());
    this->SetDefensivePower(up.GetReference(towercode).GetDefensivePower());
    this->SetAttackSpeed(up.GetReference(towercode).GetAttackSpeed());
}

Tower* Tower::fuseTower(Tower *tow1, Tower *tow2)
{
    /*타워 조합 공식
     * @@1+1=2@@
     * NORMAL + SLOW = PROF 0*2 = 2
     * SPLASH + CHAIN = TUTOR 1*4 = 4
     * SPLASH + GOLD = MES 1*5 = 5
     * POISON + GOLD = CES 3*5 = 15
     * CHAIN + GOLD = JOBSBIO 4*5 = 20
     *
     * @@2+2=3@@
     * TUTOR + JOBSBIO = APPLE 6*9 = 54
     * PROF + JOBSBIO = JOBS 7*9 = 63
     * CES + MES = TRIPLE 8*10=80*/
    //필수사항 : 만드시 조합가능한거 끼리만 이 함수에 들어올수 있도록 해야함, 아니면 조합이
    //안되는 두가지 임에도 불구하고 조합이 되어 나갈수도 있음!!
    int mult_code = tow1->GetTowerCode()*tow2->GetTowerCode();
    delete tow1;
    delete tow2;                    //재료가 되는 두 타워는 지움
    switch(mult_code){
    case 2:
        return new ProfessorMeeting();
    case 4:
        return new TutorRobot();
    case 5:
        return new MetalEngSenior();
    case 15:
        return new ChemEngSenior();
    case 20:
        return new JobsBiography();
    case 54:
        return new AppleRobot();
    case 63:
        return new SteveJobs();
    case 80:
        return new TripleMajorSenior();     //조합에 따라 알맞은 타워 반환
    }
}

<<<<<<< HEAD
<<<<<<< HEAD
void Tower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!choose && !game->add_mode){
        if(game->waiting_line.size() < 2){
           attack_area->setPen(QPen(Qt::SolidLine));
           choose = true;
           game->waiting_line.push_back(this);
        }
    }

    else{
      attack_area->setPen(QPen(Qt::DotLine));
        choose = false;
        if(game->waiting_line[0] == this)
            game->waiting_line.remove(0);
        else
           game->waiting_line.remove(1);
    }
}

void Tower::aquire_target()
=======
int Tower::GetTargetNum()
>>>>>>> origin/BattleObject-&-Tower
{
    return TargetNum;
}

=======
int Tower::GetTargetNum()
{
    return TargetNum;
}

>>>>>>> BattleObject-&-Tower
int Tower::GetTowerCode()
{
    return TowerCode;
}
