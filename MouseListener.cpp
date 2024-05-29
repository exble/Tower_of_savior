#include "MouseListener.h"
#include "Game.h"

extern Game* game;

MouseListener::MouseListener()
{
    game->MouseListeners.push_back(this);
}

MouseListener::~MouseListener()
{
    game->MouseListeners.removeOne(this);
}

void MouseListener::MousePressEvent(const QGraphicsSceneMouseEvent *event)
{
    if(event){

    }
}

void MouseListener::MouseReleaseEvent(const QGraphicsSceneMouseEvent *event)
{
    if(event){

    }
}

void MouseListener::MouseMoveEvent(const QGraphicsSceneMouseEvent *event)
{
    if(event){

    }
}
