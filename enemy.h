#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include<QWidget>

class Enemy : public QObject, public QGraphicsRectItem{
Q_OBJECT
private:
    float path[10][2];
    int currentPath;
    int clockRate;
    float x_move;
    float y_move;
public:
    Enemy(int level=1);
public slots:
    void move();
};


#endif // ENEMY_H

