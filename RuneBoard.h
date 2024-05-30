#ifndef RUNEBOARD_H
#define RUNEBOARD_H

#include "Object.h"
#include "MouseListener.h"
#include "Rune.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

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
    void generateRunes();
    void checkLink();
    void makeCluster();
    void updatePosition();
    void handle_spinning();
    void handle_linking();
    void handle_dropping();
    void setState(RuneBoardState state);
    RuneBoardState getState() const;
    static Rune* getRandRune();
    static QPoint CordToIndex(QPointF point);
    static QPointF IndexToCord(QPoint point);

public:

private:
    Rune* runes[RUNE_COUNT_X][RUNE_COUNT_Y] = {};
    bool markMap[RUNE_COUNT_X][RUNE_COUNT_Y] = {};
    RuneBoardState state;
    QTimer* timer;
    QList<QList<QPoint>> clusters;
    QGraphicsPixmapItem* dummy_rune = nullptr;
    Rune* holding_rune = nullptr;
    CheckBoard* backBoard = nullptr;
    int linking_index;
    int attack = 0;
    int healing = 0;
    QPointF mouse_cord;
};

#endif // RUNEBOARD_H
