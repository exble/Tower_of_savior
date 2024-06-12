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
class DamageBox;

class TitleScreen;
class tsMouseMove;
class TeamMouseMove;
class TeamScreen;
class ReadyMouseMove;
class ReadyScreen;

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

    TitleScreen *getTitleScreen() const;
    TeamScreen *getTeamScreen() const;
    ReadyScreen *getReadyScreen() const;
    void ChangeScreentoTitle();
    void ChangeScreentoTeam();
    void ChangeScreentoReady();



    void showLose();
    void showWin();
    void showSurrender();
    void Restart();
    void goBack();

    void setPlayerHp(int newPlayerHp);
    void PlayerHpMinus(int minusHp);

public:
    QPixmap character1 = QPixmap(":/character/dataset/character/ID1.png");
    QPixmap character2 = QPixmap(":/character/dataset/character/ID2.png");
    QPixmap character3 = QPixmap(":/character/dataset/character/ID3.png");
    QPixmap character4 = QPixmap(":/character/dataset/character/ID4.png");
    QPixmap character5 = QPixmap(":/character/dataset/character/ID5.png");
    QPixmap member1;
    QPixmap member2;
    QPixmap member3;
    QPixmap member4;
    QPixmap member5;
    QPixmap member6;
    const int Teamsize = 6;
    QList<int> member;
    QList<QPixmap> characterType{character1,character2,character3,character4,character5};
    QList<QGraphicsPixmapItem*> TeamMember;
    QGraphicsPixmapItem* TeamMember1 = nullptr;
    QGraphicsPixmapItem* TeamMember2 = nullptr;
    QGraphicsPixmapItem* TeamMember3 = nullptr;
    QGraphicsPixmapItem* TeamMember4 = nullptr;
    QGraphicsPixmapItem* TeamMember5 = nullptr;
    void setCharacterSlot(CharacterSlot *newCharacterSlot);

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
    DamageBox* db;
    QTimer* battletimer;
    int playerHp = 0;
    int BattleIndex = 0;
    QGraphicsPixmapItem* backgroundItem;
    BGM* bgm;  // Add BGM member

    TitleScreen* titleScreen;
    tsMouseMove* TsMouseMove;
    TeamScreen* teamScreen;
    TeamMouseMove* teamMouseMove;
    ReadyScreen* readyScreen;
    ReadyMouseMove* readyMouseMove;

private slots:
    void update();
};

#endif // GAME_H
