#ifndef TITLEANDINTRO
#define TITLEANDINTRO

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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

    QMediaPlayer player;
    QMediaPlaylist playlist;

    int page_num;

private:


};


#endif // TITLEANDINTRO

