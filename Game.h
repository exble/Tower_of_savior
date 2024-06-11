#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>
#include "BGM.h"  // Include the BGM header file

class RuneBoard;
class Object;
class MouseListener;
class TickListener;
class MouseMove;
class PlayerStatusBar;
class CharacterSlot;
class Battle;
class NotifyWindow;
class SettingButton;

class Game : public QObject {
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
    RuneBoard* getBoard() const;
    Battle* getCurrentBattle() const;
    void nextBattle();
    CharacterSlot* getCharacterSlot() const;
    void setBackgroundImage(const QString &imagePath);

    void showLose();
    void showWin();
    void showSurrender();
    void Restart();
    void goBack();

    void setPlayerHp(int newPlayerHp);

private:
    void initBattles();
    void initWindows();
private:
    QTimer* tick;
    QGraphicsScene* scene;
    QGraphicsView* view;
    RuneBoard* board;
    MouseMove* mousemove;
    PlayerStatusBar* PlayerBar;
    CharacterSlot* characterSlot;
    std::array<Battle*, 3> battles;
    Battle* currentBattle;
    NotifyWindow* SurrenderWindow;
    NotifyWindow* winWindow;
    NotifyWindow* loseWindow;
    SettingButton* sb;
    QTimer* battletimer;
    int playerHp = 0;
    int BattleIndex = 0;
    QGraphicsPixmapItem* backgroundItem;
    BGM* bgm;  // Add BGM member

private slots:
    void update();
};

#endif // GAME_H
