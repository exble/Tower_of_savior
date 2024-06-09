#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "MouseListener.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>

class TitleScreen : public MouseListener{
public:
    TitleScreen();
    static QGraphicsScene* titleScene;
    static TitleScreen* instance;
    QGraphicsPixmapItem* background;
    QRectF bottom;
    void ScreenChange();

private:
    void restart_tick();
    QPixmap originalPixmap;
    QPixmap TeamPixmap;
    QPixmap ReadyPixmap;
    int Picture = 0;

};

class tsMouseMove : public QGraphicsRectItem{
public:
    tsMouseMove();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};


#endif // TITLESCREEN_H
