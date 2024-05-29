#ifndef MOUSEMOVE_H
#define MOUSEMOVE_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class MouseMove : public QGraphicsRectItem{
public:
    MouseMove();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // MOUSEMOVE_H
