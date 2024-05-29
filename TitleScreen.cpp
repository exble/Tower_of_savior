#include "TitleScreen.h"
#include "Game.h"
#include "param.h"

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>

extern Game* game;

TitleScreen::TitleScreen() {
    titleScene = new QGraphicsScene();
    background = new QGraphicsPixmapItem();
    QPixmap originalPixmap(":/other/dataset/other/select2.png");
    QPixmap scaledPixmap = originalPixmap.scaled(GAME_WIDTH, GAME_HEIGHT, Qt::KeepAspectRatio);
    background->setPixmap(scaledPixmap);
    game->getScene()->addItem(background);
    background->setPos(0, 0);
    titleScene->addItem(background);
}
