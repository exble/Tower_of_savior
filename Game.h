#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

class RuneBoard;
class Object;
class MouseListener;
class MouseMove;

class Game: public QObject{
    Q_OBJECT
public:
    Game() = default;
    void start();
    QTimer* getTick() const;
    QGraphicsScene* getScene() const;
    QGraphicsView* getView() const;
    QList<Object*> Object_list;
    QList<MouseListener*> Listener_list;

private:
    QTimer* tick;
    QGraphicsScene* scene;
    QGraphicsView* view;
    RuneBoard* board;
    MouseMove* mousemove;

private slots:
    void update();
};

#endif // GAME_H
