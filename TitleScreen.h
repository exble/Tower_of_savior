#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "MouseListener.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>

class TitleScreen : public MouseListener{
public:
    TitleScreen();
    QGraphicsScene* titleScene;
    QGraphicsPixmapItem* background;
    QRectF bottom;
    void ScreenChange();
    void mousePressEvent(QMouseEvent);
    void mouseMoveEvent(QMouseEvent);
    void mouseReleaseEvent(QMouseEvent);
    Qt::MouseButton Lbuttom = Qt::LeftButton;

private:
    void restart_tick();
};

#endif // TITLESCREEN_H
