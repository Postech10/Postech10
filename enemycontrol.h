#ifndef ENEMYCONTROL
#define ENEMYCONTROL

#include "enemy.h"
#include "attackableenemy.h"
#include <QGraphicsScene>
#include <QObject>


class EnemyControl:public QObject{
    Q_OBJECT
private:
    Enemy* list[10];
    QGraphicsScene* ttt;
    int enemyNum;
    int enemyLevel;
public:
    EnemyControl(int level, QGraphicsScene* scene);
    void increaseLevel(int level);
public slots:
    void spawn();
};

#endif // ENEMYCONTROL

