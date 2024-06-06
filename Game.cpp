#include "Game.h"
#include "Config.h"
#include "Object.h"
#include "RuneBoard.h"
#include "MouseMove.h"
#include "StatusBar.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

using namespace Constants;

void Game::start()
{
    // setup QGraphicsView
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(GameWidth, GameHeight);
    scene->setSceneRect(0, 0, GameWidth, GameHeight);
    view->setScene(scene);
    view->show();

    // init game tick
    tick = new QTimer();
    tick->start(1000.0/TickPerSec);
    connect(tick, SIGNAL(timeout()), this, SLOT(update()));

    // init MouseMove
    mousemove = new MouseMove();

    // init rune board
    board = new RuneBoard();



}

void Game::update()
{
    // update all TickListeners
    foreach(TickListener* tick_reader, TickListeners){
        tick_reader->update_handler();
    }

}

QTimer* Game::getTick() const
{
    return tick;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}

QGraphicsView *Game::getView() const
{
    return view;
}


