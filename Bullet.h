#ifndef BULLET
#define BULLET

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet();           //constructor
public slots:
    void move();        //bullet move method
private:
};

#endif // BULLET

