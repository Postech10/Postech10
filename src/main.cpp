#include <QApplication>
#include "Game.h"
#include "titleandintro.h"

TitleAndIntro* title;
Game *game;                             //?꾩뿭 蹂???좎뼵
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    title = new TitleAndIntro();
    game = new Game();
    title->show();



    return a.exec();
}
