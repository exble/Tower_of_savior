#include "Game.h"
#include "param.h"
#include "Object.h"
#include "CheckBoard.h"

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

    // init board
    board = new CheckBoard();
    board->placeBoard();
}

void Game::update()
{
    // update all objects
    foreach(Object* obj, Object_list){
        obj->update_handler();
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


