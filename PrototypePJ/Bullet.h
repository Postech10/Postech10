#ifndef BULLET
#define BULLET

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int);           //constructor, int는 bullet의 파괴력(?)을 뜻함
    void SetAttackPower(int);
    int GetAttackPower();
public slots:
    void move();        //bullet move method
protected:
    int AttackPower;        //Bullet의 파괴력
};

#endif // BULLET

