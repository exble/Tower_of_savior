#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

class QGraphicsSceneMouseEvent;

class MouseListener{
public:
    MouseListener();
    virtual ~MouseListener();
    virtual void MousePressEvent(const QGraphicsSceneMouseEvent* event);
    virtual void MouseReleaseEvent(const QGraphicsSceneMouseEvent* event);
    virtual void MouseMoveEvent(const QGraphicsSceneMouseEvent* event);
};

#endif // MOUSELISTENER_H
