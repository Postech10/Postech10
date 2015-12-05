#ifndef BUILDTOWERICON
#define BUILDTOWERICON
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QMovie>
#include <Tower.h>
#include <cstdlib>
#include <ctime>

class BuildTowerIcon: public QPushButton,public QGraphicsPixmapItem{

    int tower_code;

public:
    BuildTowerIcon(char* filename,int _tower_code,QGraphicsItem *parent =0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);      //?꾨? ??method

    int getTowerCode() {return tower_code;}
    void setTowerCode(int _tower_code) {tower_code = _tower_code;}

    void updatePixmap(BuildTowerIcon*update, char *newImage);
};

#endif // BUILDTOWERICON
