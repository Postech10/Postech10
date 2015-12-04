#ifndef BUILDTOWERICON
#define BUILDTOWERICON
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QMovie>
#include <Tower.h>

class BuildTowerIcon: public QPushButton,public QGraphicsPixmapItem{

    int tower_code;

public:
    BuildTowerIcon(char* filename,int _tower_code,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //?꾨? ??method
};

#endif // BUILDTOWERICON
