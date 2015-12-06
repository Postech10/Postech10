#include "titleandintro.h"
#include <QPixmap>
#include <QFontDatabase>
#include <QString>
#include <QDebug>
#include <Game.h>
#include <QApplication>
#include <QRect>

extern Game* game;
TitleAndIntro::TitleAndIntro()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1024, 768);
    setFixedSize(1024, 768);
    setScene(scene);

    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap* title = new QPixmap(":/images/TitleScreen.bmp");
    scene->addPixmap(*title);



    page_num = 1;

    start = new Button(":/images/TitleButton.bmp");
    start->QGraphicsPixmapItem::setPos(384, 576);
    //start->resize(QSize(704-384, 704-576));
    //start->setGeometry(384, 576, 704-384, 704-576);
    start->setZValue(1);
    scene->addItem(start);

    credit = new Button(":/images/button_credit.bmp");
    credit->setPos(128, 704);
    credit->setGeometry(128, 704, 384-128, 768-704);
    credit->setZValue(1);
    scene->addItem(credit);

    exit = new Button(":/images/button_exit.bmp");
    exit->setPos(768, 704);
    exit->setGeometry(768, 704, 896-768, 768-704);
    exit->setZValue(1);
    scene->addItem(exit);

    next = new Button(":/images/button_next(blue).bmp");
    next->setPos(832, 640);
    next->setZValue(1);
}


void TitleAndIntro::button_Pressed(QPointF point)
{
    qreal x = point.x();
    qreal y = point.y();

    qreal next_x = next->QGraphicsPixmapItem::pos().x();
    qreal next_y = next->QGraphicsPixmapItem::pos().y();
    qreal next_width = next->QGraphicsPixmapItem::pixmap().width();
    qreal next_height = next->QGraphicsPixmapItem::pixmap().height();

    switch(page_num)
    {

    case 1:
        if(x >= exit->QGraphicsPixmapItem::pos().x() &&
                x <= exit->QGraphicsPixmapItem::pos().x() + exit->QGraphicsPixmapItem::pixmap().width() &&
                y >= exit->QGraphicsPixmapItem::pos().y() &&
                y <= exit->QGraphicsPixmapItem::pos().y() + exit->QGraphicsPixmapItem::pixmap().height())
        {
            QApplication::quit();
        }
        else if(x >= credit->QGraphicsPixmapItem::pos().x() &&
                x <= credit->QGraphicsPixmapItem::pos().x() + credit->QGraphicsPixmapItem::pixmap().width() &&
                y >= credit->QGraphicsPixmapItem::pos().y() &&
                y <= credit->QGraphicsPixmapItem::pos().y() + credit->QGraphicsPixmapItem::pixmap().height())
        {
            /*scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro2.bmp"));
            page_num = 0;*/
        }
        else if(x >= start->QGraphicsPixmapItem::pos().x() &&
                x <= start->QGraphicsPixmapItem::pos().x() + start->QGraphicsPixmapItem::pixmap().width() &&
                y >= start->QGraphicsPixmapItem::pos().y() &&
                y <= start->QGraphicsPixmapItem::pos().y() + start->QGraphicsPixmapItem::pixmap().height())
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro1.bmp"));
            page_num = 2;

            scene->addItem(next);
        }

        break;

    case 2:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro2.bmp"));
            page_num = 3;

            next = new Button(":/images/button_next(blue).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 3:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro3.bmp"));
            page_num = 4;

            next = new Button(":/images/button_next(brown).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 4:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro4.bmp"));
            page_num = 5;

            next = new Button(":/images/button_next(black).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 5:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro5.bmp"));
            page_num = 6;

            next = new Button(":/images/button_next(black).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 6:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro6.bmp"));
            page_num = 7;

            next = new Button(":/images/button_next(black).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 7:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro7.bmp"));
            page_num = 8;

            next = new Button(":/images/button_next(black).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 8:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro8.bmp"));
            page_num = 9;

            next = new Button(":/images/button_start.bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(next);
        }
        break;

    case 9:
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            page_num = 10;
            this->close();
            game = new Game();
            game->displayMenu();
            game->show();
        }
        break;
    default:
        break;
    }

    //credit and exit
    //else if()
}

