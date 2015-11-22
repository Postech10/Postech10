#ifndef BUILDTOWERICON
#define BUILDTOWERICON
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <Tower.h>

class BuildTowerIcon: public QPushButton, public QGraphicsPixmapItem{

    int tower_code;

public:
    BuildTowerIcon(char* filename,int _tower_code,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //누를 때 method
};

#endif // BUILDTOWERICON
