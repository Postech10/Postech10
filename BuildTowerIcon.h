#ifndef BUILDTOWERICON
#define BUILDTOWERICON
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
class BuildTowerIcon: public QGraphicsPixmapItem{
public:
    BuildTowerIcon(QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method
};

#endif // BUILDTOWERICON
