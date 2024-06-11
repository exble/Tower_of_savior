#ifndef RUNEBOARD_H
#define RUNEBOARD_H
#include <QGraphicsTextItem>
#include "TickListener.h"
#include "MouseListener.h"
#include "Rune.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class CheckBoard;
class StatusBar;

class RuneBoard : public TickListener, public MouseListener{
public:
    RuneBoard();
    RuneBoardState getState() const;
    void setState(RuneBoardState state);
    QTimer *getCountDownTimer() const;
    Rune* getRune(int x, int y);
    void setFire(bool sel);
    void resetBoard();
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
    void handleSpinning();
    void handleLinking();
    void handleDropping();
    void triggerLinking();
    void triggerSpining(QPoint index);
    void setRunesOpacity(float opacity);
    void preLink();


    static Rune* getRandRune();
    static QPoint CordToIndex(QPointF point);
    static QPointF IndexToCord(QPoint point);

private:
    Rune* runes[Constants::RuneCountX][Constants::RuneCountY] = {};
    bool markMap[Constants::RuneCountX][Constants::RuneCountY] = {};
    RuneBoardState state;
    QTimer* timer;
    QTimer* CountDownTimer;
    QList<QList<QPoint>> clusters;
    QGraphicsPixmapItem* dummy_rune = nullptr;
    Rune* holding_rune = nullptr;
    CheckBoard* backBoard = nullptr;
    QGraphicsTextItem* comboTextItem;
    attackInfo atkinfo;
    bool enebleFire = false;
    int comboCnt = 0;
    int linking_index = 0;
    int attack = 0;
    int healing = 0;

    QPointF mouse_cord;
};

#endif // RUNEBOARD_H
