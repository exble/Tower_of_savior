#include "Game.h"
#include "Config.h"
#include "Object.h"
#include "RuneBoard.h"
#include "MouseMove.h"
#include "PlayerStatusBar.h"
#include "CharacterSlot.h"
#include "Enemy.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

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

    // init game tick
    tick = new QTimer();
    tick->start(1000.0/TickPerSec);
    connect(tick, SIGNAL(timeout()), this, SLOT(update()));

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

    Enemy* enemy;
    //enemy = new Enemy(MonsterType::LightSlime);
    //enemy->setPos(100, 200);
    //scene->addItem(enemy);
    //enemy = new Enemy(MonsterType::DarkSlime);
    //enemy->setPos(320, 200);
    //scene->addItem(enemy);

    enemy = new Enemy(MonsterType::HellHound);
    enemy->setPos(140, 50);
    scene->addItem(enemy);

    playerHp = PlayerMaxHP;
}

void Game::update()
{
    // update all TickListeners
    foreach(TickListener* tick_reader, TickListeners){
        tick_reader->update_handler();
    }

}

QTimer* Game::getTick() const
{
    return tick;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}

QGraphicsView *Game::getView() const
{
    return view;
}

PlayerStatusBar *Game::getPlayerBar() const
{
    return PlayerBar;
}

int Game::getPlayerHp() const
{
    return playerHp;
}

RuneBoard *Game::getBoard() const
{
    return board;
}



