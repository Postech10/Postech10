#ifndef BUILDTOWERICON
#define BUILDTOWERICON
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>

class BuildTowerIcon: public QPushButton ,public QGraphicsPixmapItem{

public:
    BuildTowerIcon(char* filename,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method
};

#endif // BUILDTOWERICON
