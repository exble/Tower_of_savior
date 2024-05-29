#ifndef RUNEBOARD_H
#define RUNEBOARD_H

#include "Object.h"
#include "MouseListener.h"
#include "Rune.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class CheckBoard;

class RuneBoard : public Object, public MouseListener{
public:
    RuneBoard();
private:
    void update();
    void MousePressEvent(const QGraphicsSceneMouseEvent* event);
    void MouseReleaseEvent(const QGraphicsSceneMouseEvent* event);
    void MouseMoveEvent(const QGraphicsSceneMouseEvent* event);

    void initBoard();
    void drop();
    void checkLink();
    void updatePosition();
    void moving();
    static Rune* getRandRune();
    // row major
    static QPoint CordToIndex(QPointF point);
public:

private:
    Rune* runes[RUNE_COUNT_X][RUNE_COUNT_Y] = {};
    QGraphicsPixmapItem* dummy_rune = nullptr;
    Rune* holding_rune = nullptr;
    CheckBoard* backBoard = nullptr;
    QGraphicsSceneMouseEvent* mEnent = nullptr;
    int attack = 0;
    int healing = 0;
    bool is_holding = 0;
    QPointF mouse_cord;
};

#endif // RUNEBOARD_H
