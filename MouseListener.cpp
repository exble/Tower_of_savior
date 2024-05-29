#include "MouseListener.h"
#include "Game.h"

extern Game* game;

MouseListener::MouseListener()
{
    game->Listener_list.push_back(this);
}

MouseListener::~MouseListener()
{
    game->Listener_list.removeOne(this);
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
