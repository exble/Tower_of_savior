#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "Game.h"
#include "param.h"

void Game::start()
{
    tick.start(1000/TICK_PER_SEC);
    connect(&tick, SIGNAL(tick.timeout()), this, SLOT(update()));


}

const QTimer &Game::getTick() const
{
    return tick;
}

void Game::update()
{

}
