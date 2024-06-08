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
class PlayerStatusBar;
class CharacterSlot;

class Game: public QObject{
    Q_OBJECT
public:
    Game() = default;
    void start();
    QTimer* getTick() const;
    QGraphicsScene* getScene() const;
    QGraphicsView* getView() const;
    PlayerStatusBar* getPlayerBar() const;
    int getPlayerHp() const;
    QList<Object*> Object_list;
    QList<MouseListener*> MouseListeners;
    QList<TickListener*> TickListeners;
    RuneBoard *getBoard() const;
private:
    QTimer* tick;
    QGraphicsScene* scene;
    QGraphicsView* view;
    RuneBoard* board;
    MouseMove* mousemove;
    PlayerStatusBar* PlayerBar;
    CharacterSlot* characterSlot;
    int playerHp;

private slots:
    void update();
};

#endif // GAME_H
