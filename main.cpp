#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Game.h"
#include <QMouseEvent>

Game *game;                             //전역 변수 선언
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    game = new Game();                  //초기화
    game->displayMenu();                //메뉴 추가
    game->show();                       //화면출력

    return a.exec();
}
