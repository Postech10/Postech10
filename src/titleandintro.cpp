#include "titleandintro.h"
#include <QPixmap>
#include <QFontDatabase>
#include <QString>
#include <QDebug>
#include <Game.h>
#include <QApplication>
#include <QRect>
#include <QUrl>
#include "Game.h"

extern Game* game;
TitleAndIntro::TitleAndIntro()
{
    scene = new QGraphicsScene(this); // make scene
    scene->setSceneRect(0, 0, 1024, 768);
    setFixedSize(1024, 768);
    setScene(scene);

    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // remove scrollbar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap* title = new QPixmap(":/images/TitleScreen.bmp"); // set scene pixmap to TitleScreen
    scene->addPixmap(*title);



    page_num = 1;

    start = new Button(":/images/TitleButton.bmp"); // make 4 buttons: start, credit, exit, next
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

    playlist.addMedia(QUrl::fromLocalFile("resources/sounds/TitleTheme.mp3"));
    playlist.addMedia(QUrl::fromLocalFile("resources/sounds/tutorial.mp3"));
    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);



    player.setPlaylist(&playlist);
    player.play();
}


void TitleAndIntro::button_Pressed(QPointF point) // called when button pressed
{
    qreal x = point.x();
    qreal y = point.y();

    qreal next_x = next->QGraphicsPixmapItem::pos().x();
    qreal next_y = next->QGraphicsPixmapItem::pos().y();
    qreal next_width = next->QGraphicsPixmapItem::pixmap().width();
    qreal next_height = next->QGraphicsPixmapItem::pixmap().height();

    switch(page_num)
    {
    case 0: //credit screen
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/TitleScreen.bmp"));
            page_num = 1;

            next = new Button(":/images/button_next(blue).bmp");
            next->setPos(832, 640);
            next->setZValue(1);
            scene->addItem(start);
            scene->addItem(credit);
            scene->addItem(exit);
        }
        break;

    case 1:
        if(x >= exit->QGraphicsPixmapItem::pos().x() && // if exit button contains point
                x <= exit->QGraphicsPixmapItem::pos().x() + exit->QGraphicsPixmapItem::pixmap().width() &&
                y >= exit->QGraphicsPixmapItem::pos().y() &&
                y <= exit->QGraphicsPixmapItem::pos().y() + exit->QGraphicsPixmapItem::pixmap().height())
        {
            QApplication::quit(); // quit application
        }
        else if(x >= credit->QGraphicsPixmapItem::pos().x() && // if credit button contains point
                x <= credit->QGraphicsPixmapItem::pos().x() + credit->QGraphicsPixmapItem::pixmap().width() &&
                y >= credit->QGraphicsPixmapItem::pos().y() &&
                y <= credit->QGraphicsPixmapItem::pos().y() + credit->QGraphicsPixmapItem::pixmap().height())
        {
            scene->removeItem(start);
            scene->removeItem(credit);
            scene->removeItem(exit);
            scene->addPixmap(QPixmap(":/images/Credit.bmp"));
            page_num = 0;

            scene->addItem(next);
        }
        else if(x >= start->QGraphicsPixmapItem::pos().x() && //
                x <= start->QGraphicsPixmapItem::pos().x() + start->QGraphicsPixmapItem::pixmap().width() &&
                y >= start->QGraphicsPixmapItem::pos().y() &&
                y <= start->QGraphicsPixmapItem::pos().y() + start->QGraphicsPixmapItem::pixmap().height())
        {
            scene->clear();
            scene->addPixmap(QPixmap(":/images/Intro1.bmp"));
            page_num = 2;

            scene->addItem(next);
            playlist.setCurrentIndex(1);
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

    case 9: // end of intro and tutorial
        if(x >= next_x && x <= next_x + next_width && y >= next_y && y <= next_y + next_height)
        {
            page_num = 10;
            player.stop();
            this->close();
            game = new Game(); // make new Game
            game->displayMenu();
            game->show(); // show game
        }
        break;
    default:
        break;
    }

    //credit and exit
    //else if()
}

