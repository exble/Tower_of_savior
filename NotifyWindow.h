#ifndef NOTIFYWINDOW_H
#define NOTIFYWINDOW_H

#include "Game.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Button: public QGraphicsRectItem{
    friend class NotifyWindow;
public:
    Button(QString text, QColor backcolor, QColor textcolor, QGraphicsRectItem* parent);
    ~Button();
    void setFunction(void (Game::*)(void));
    void positionCenter();
    void setBackGround(bool sel);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
private:
    QGraphicsTextItem* textbox = nullptr;
    void (Game::*Func)(void) = nullptr;
    QGraphicsRectItem* parent;
};


class NotifyWindow: public QGraphicsRectItem{
public:
    NotifyWindow();
    void show();
    void hide();
    void addButton(Button* button);
    bool getIsActive() const;

private:
    QList<Button*>buttons;
    bool isActive = false;
};

#endif // NOTIFYWINDOW_H
