#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Game.h"
#include <QMouseEvent>

Game *game;                             //?꾩뿭 蹂???좎뼵
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    game = new Game();                  //珥덇린??
    game->displayMenu();                //硫붾돱 異붽?
    game->show();                       //?붾㈃異쒕젰

    return a.exec();
}
