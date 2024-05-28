#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

class CheckBoard;
class Object;


class Game: public QObject{
    Q_OBJECT
public:
    Game() = default;
    void start();
    QTimer* getTick() const;
    QGraphicsScene *getScene() const;
    QGraphicsView *getView() const;
    QList<Object*> Object_list;

private:
    QTimer* tick;
    QGraphicsScene* scene;
    QGraphicsView* view;
    CheckBoard* board;


private slots:
    void update();
};

#endif // GAME_H
