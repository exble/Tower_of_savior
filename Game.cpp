#include "Game.h"
#include "Config.h"
#include "Object.h"
#include "RuneBoard.h"
#include "MouseMove.h"
#include "PlayerStatusBar.h"
#include "CharacterSlot.h"
#include "Enemy.h"
#include "Battle.h"
#include "BGM.h"  // Include the BGM header file

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QUrl>

using namespace Constants;

void Game::start()
{
    // setup QGraphicsView
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(GameWidth, GameHeight);
    scene->setSceneRect(0, 0, GameWidth, GameHeight);
    view->setScene(scene);
    view->show();

    // init background item
    backgroundItem = new QGraphicsPixmapItem();
    scene->addItem(backgroundItem);

    // init game tick
    tick = new QTimer();
    tick->start(1000.0 / TickPerSec);
    connect(tick, SIGNAL(timeout()), this, SLOT(update()));

    // init battle timer
    battletimer = new QTimer;
    battletimer->setSingleShot(true);

    // init MouseMove
    mousemove = new MouseMove();

    // init rune board
    board = new RuneBoard();

    // init Player Bar
    PlayerBar = new PlayerStatusBar();

    // init Character Slot
    characterSlot = new CharacterSlot();
    characterSlot->setCharacter(0, CharacterType::Fire);
    characterSlot->setCharacter(1, CharacterType::Water);
    characterSlot->setCharacter(2, CharacterType::Light);
    characterSlot->setCharacter(3, CharacterType::Dark);
    characterSlot->setCharacter(4, CharacterType::Earth);
    characterSlot->setCharacter(5, CharacterType::Fire);
    characterSlot->updatePosition();

    initBattles();

    BattleIndex = 0;

    currentBattle = battles[BattleIndex];

    currentBattle->start();

    playerHp = PlayerMaxHP;

    // init BGM
    bgm = new BGM(this);
    bgm->playBackgroundMusic("qrc:/audio/dataset/audio/BATTLE_ELEMENTAL.wav");
}

void Game::update()
{
    // update all TickListeners
    foreach (TickListener* tick_reader, TickListeners) {
        tick_reader->update_handler();
    }

    if (currentBattle->getEnemyList().size() == 0) {
        if (currentBattle->getIsFinish() == false) {
            currentBattle->setIsFinish(true);
            battletimer->start(BattleSwapDelay);
        }
        else if (currentBattle->getIsFinish() && !battletimer->isActive()) {
            nextBattle();
        }
    }
}

QTimer* Game::getTick() const
{
    return tick;
}

QGraphicsScene* Game::getScene() const
{
    return scene;
}

QGraphicsView* Game::getView() const
{
    return view;
}

PlayerStatusBar* Game::getPlayerBar() const
{
    return PlayerBar;
}

int Game::getPlayerHp() const
{
    return playerHp;
}

RuneBoard* Game::getBoard() const
{
    return board;
}

Battle* Game::getCurrentBattle() const
{
    return currentBattle;
}

int& Game::ref_playerHp()
{
    return playerHp;
}

void Game::nextBattle()
{
    BattleIndex++;
    currentBattle = battles[BattleIndex];
    currentBattle->start();
    setBackgroundImage(currentBattle->getBackgroundImagePath());

    // Change background music for Battle Three
    if (BattleIndex == 2) {
        bgm->playBackgroundMusic("qrc:/audio/dataset/audio/BOSS_ELEMENTAL.wav");
    } else {
        bgm->playBackgroundMusic("qrc:/audio/dataset/audio/BATTLE_ELEMENTAL.wav");
    }
}

CharacterSlot* Game::getCharacterSlot() const
{
    return characterSlot;
}

void Game::initBattles()
{
    // init Battles
    arrangementInfo info;
    QList<arrangementInfo> infos;

    for (int i = 0; i < 3; i++) {
        battles[i] = new Battle();
    }

    // Battle one
    info.type = MonsterType::WaterSlime;
    info.placementCord = QPoint(60, 200);
    infos.push_back(info);

    info.type = MonsterType::FireSlime;
    info.placementCord = QPoint(210, 200);
    infos.push_back(info);

    info.type = MonsterType::EarthSlime;
    info.placementCord = QPoint(360, 200);
    infos.push_back(info);

    battles[0]->setArrangement(infos);
    battles[0]->setBackgroundImagePath(":/other/dataset/other/background1.png"); // Set background image path for battle one

    // Battle two
    infos.clear();

    info.type = MonsterType::LightSlime;
    info.placementCord = QPoint(60, 200);
    infos.push_back(info);

    info.type = MonsterType::Duck;
    info.placementCord = QPoint(210, 200);
    infos.push_back(info);

    info.type = MonsterType::DarkSlime;
    info.placementCord = QPoint(360, 200);
    infos.push_back(info);

    battles[1]->setArrangement(infos);
    battles[1]->setBackgroundImagePath(":/other/dataset/other/background2.png"); // Set background image path for battle two

    // Battle three
    infos.clear();

    info.type = MonsterType::HellHound;
    info.placementCord = QPoint(140, 100);
    infos.push_back(info);

    battles[2]->setArrangement(infos);
    battles[2]->setBackgroundImagePath(":/other/dataset/other/background3.png"); // Set background image path for battle three
}

void Game::setPlayerHp(int newPlayerHp)
{
    playerHp = newPlayerHp;
    if (playerHp < 0) {
        playerHp = 0;
    }
}

void Game::setBackgroundImage(const QString& imagePath)
{
    QPixmap backgroundPixmap(imagePath);
    backgroundItem->setPixmap(backgroundPixmap);
    backgroundItem->setPos(0, 0);
    backgroundItem->setZValue(-1000); // Ensure the background is behind other items
}
