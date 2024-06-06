#include "MouseMove.h"
#include "Game.h"
#include "Config.h"
#include "Object.h"
#include "MouseListener.h"

#include <QDebug>

extern Game* game;

using namespace Constants;

MouseMove::MouseMove()
{
    setRect(0, 0, GameWidth, GameHeight);
    game->getScene()->addItem(this);

}

void MouseMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MousePressEvent(event);
    }
#if DEBUG_MOUSE
    QPointF cord = event->pos();
    qDebug() << "Mouse Pressed at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

void MouseMove::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseReleaseEvent(event);
    }
#if DEBUG_MOUSE
    QPointF cord = event->pos();
    qDebug() << "Mouse Released at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

void MouseMove::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseMoveEvent(event);
    }
#if DEBUG_MOUSE
    QPointF cord = event->pos();
    qDebug() << "Mouse Moving at x = " <<  cord.x() << " y = " << cord.y();
#endif
}
