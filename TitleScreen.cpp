#include "TitleScreen.h"
#include "TeamScreen.h"
#include "Game.h"
#include "Config.h"
#include "MouseListener.h"
#include "enum.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QRect>

QGraphicsScene* TitleScreen::titleScene = nullptr;

extern Game* game;

using namespace Constants;

TitleScreen::TitleScreen() {
    titleScene = new QGraphicsScene();
    Titlebackground = new QGraphicsPixmapItem();
    Teambackground = new QGraphicsPixmapItem();
    Readybackground = new QGraphicsPixmapItem();

    TitlePixmap = QPixmap(":/other/dataset/other/select2.png");


    scaledTitlePixmap = TitlePixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);
    Titlebackground->setPixmap(scaledTitlePixmap);
    Titlebackground->setPos(0, 0);

    titleScene->addItem(Titlebackground);
    Type = Title;

    #if DEBUG_SCREEN
        qDebug() << "TitleScreen initialized.";
    #endif
}



void TitleScreen::ScreenChangetoTeam() {
#if DEBUG_SCREEN
    qDebug() << "ScreenChangetoTeam()";
#endif
    titleScene->removeItem(Titlebackground);
    titleScene->clear();

    game->ChangeScreentoTeam();

    #if DEBUG_SCREEN
        qDebug() << "ScreenChangetoTeam() completed, TitleScreen instance deleted.";
    #endif

}

tsMouseMove::tsMouseMove() {
    setRect(0, 0, GameWidth, GameHeight);
    TitleScreen::titleScene->addItem(this);
}

void tsMouseMove::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QPointF cord = event->pos();
    foreach(MouseListener* listener, game->MouseListeners) {
        listener->MousePressEvent(event);
    }
    #if DEBUG_SCREEN
        qDebug() << "Mouse Pressed at x = " << cord.x() << " y = " << cord.y();
    #endif
    if (cord.x() > 200 && cord.x() < 375 && cord.y() > 180 && cord.y() < 585) {
        game->getTitleScreen()->ScreenChangetoTeam();
    }
}

void tsMouseMove::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    foreach(MouseListener* listener, game->MouseListeners) {
        listener->MouseReleaseEvent(event);
    }
    #if DEBUG_SCREEN
        QPointF cord = event->pos();
        qDebug() << "Mouse Released at x = " << cord.x() << " y = " << cord.y();
    #endif
}

void tsMouseMove::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    foreach(MouseListener* listener, game->MouseListeners) {
        listener->MouseMoveEvent(event);
    }
    #if DEBUG_SCREEN
        QPointF cord = event->pos();
        qDebug() << "Mouse Moving at x = " << cord.x() << " y = " << cord.y();
    #endif
}
