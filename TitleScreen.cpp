#include "TitleScreen.h"
#include "Game.h"
#include "Config.h"
#include "MouseListener.h"


#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QRect>

QGraphicsScene* TitleScreen::titleScene = nullptr;
TitleScreen* TitleScreen::instance = nullptr;

extern Game* game;

using namespace Constants;

TitleScreen::TitleScreen() {
    titleScene = new QGraphicsScene();
    background = new QGraphicsPixmapItem();

    originalPixmap = QPixmap(":/other/dataset/other/select2.png");
    TeamPixmap = QPixmap(":/other/dataset/other/select0.png");
    ReadyPixmap = QPixmap(":/other/dataset/other/select1.png");
    QPixmap scaledPixmap = TitleScreen::originalPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);         //                                                                               1
    background->setPixmap(scaledPixmap);
    game->getScene()->addItem(background);
    background->setPos(0, 0);
    titleScene->addItem(background);
    tsMouseMove();
}

void TitleScreen::ScreenChange()
{

    #if DEBUG_SCREEN
        qDebug() << "ScreenChange  ";
    #endif
    if(TitleScreen::originalPixmap== TitleScreen::originalPixmap ){
        #if DEBUG_SCREEN
            qDebug() << "originalPixmap  ";
        #endif
        QPixmap localscaledPixmap = TitleScreen::TeamPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);         //                                                                               1
        background->setPixmap(localscaledPixmap);
        game->getScene()->addItem(background);
        background->setPos(0, 0);
        titleScene->addItem(background);
    }
    else if(TitleScreen::background->pixmap()== TitleScreen::TeamPixmap){
        #if DEBUG_SCREEN
            qDebug() << "TeamPixmap  ";
        #endif
        QPixmap scaledPixmap = TitleScreen::ReadyPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);         //                                                                               1
        background->setPixmap(scaledPixmap);
    }
    else if(TitleScreen::background->pixmap()== TitleScreen::ReadyPixmap){
        #if DEBUG_SCREEN
            qDebug() << "ReadyPixmap  ";
        #endif
        delete(this);
    }
}


tsMouseMove::tsMouseMove()
{
    setRect(0, 0, GameWidth, GameHeight);
    TitleScreen::titleScene->addItem(this);
}

void tsMouseMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cord = event->pos();
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MousePressEvent(event);
    }
#if DEBUG_SCREEN
    qDebug() << "Mouse Pressed at x = " <<  cord.x() << " y = " << cord.y();
#endif
    if(cord.x() > 100){
        TitleScreen::instance->ScreenChange();
    }
}

void tsMouseMove::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseReleaseEvent(event);
    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Released at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

void tsMouseMove::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseMoveEvent(event);
    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Moving at x = " <<  cord.x() << " y = " << cord.y();
#endif
}
