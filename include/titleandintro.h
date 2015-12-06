#ifndef TITLEANDINTRO
#define TITLEANDINTRO

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QLabel>
#include "button.h"

class TitleAndIntro : public QGraphicsView
{

public:

    TitleAndIntro();

    void button_Pressed(QPointF point);

    QGraphicsScene* scene;

    Button* start;
    Button* credit;
    Button* exit;
    Button* next;

    int page_num;

private:


};


#endif // TITLEANDINTRO

