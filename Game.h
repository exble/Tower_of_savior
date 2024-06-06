#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

class RuneBoard;
class Object;
class MouseListener;
class TickListener;
class MouseMove;
class StatusBar;

class Game: public QObject{
    Q_OBJECT
public:
    Game() = default;
    void start();
    QTimer* getTick() const;
    QGraphicsScene* getScene() const;
    QGraphicsView* getView() const;
    QList<Object*> Object_list;
    QList<MouseListener*> MouseListeners;
    QList<TickListener*> TickListeners;

private:
    QTimer* tick;
    QGraphicsScene* scene;
    QGraphicsView* view;
    RuneBoard* board;
    MouseMove* mousemove;
    StatusBar* bar;

private slots:
    void update();
};

#endif // GAME_H
