#include "TitleScreen.h"
#include "Game.h"
#include "Config.h"

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>

extern Game* game;

using namespace Constants;

TitleScreen::TitleScreen() {
    titleScene = new QGraphicsScene();
    background = new QGraphicsPixmapItem();
    QPixmap originalPixmap(":/other/dataset/other/select2.png");
    QPixmap scaledPixmap = originalPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);
    background->setPixmap(scaledPixmap);
    game->getScene()->addItem(background);
    background->setPos(0, 0);
    titleScene->addItem(background);
}
