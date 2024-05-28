#include "Game.h"

#include <QApplication>

Game* game;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    game = new Game();
    game->start();


    return app.exec();
}
