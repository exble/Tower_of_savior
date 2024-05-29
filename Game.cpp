#include "Game.h"
#include "param.h"
#include "Object.h"
#include "RuneBoard.h"
#include "MouseMove.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>


void Game::start()
{
    // setup QGraphicsView
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    scene->setSceneRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
    view->setScene(scene);
    view->show();

    // init game tick
    tick = new QTimer();
    tick->start(1000.0/TICK_PER_SEC);
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


