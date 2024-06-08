#include "Battle.h"
#include "Enemy.h"
#include "Game.h"
#include "CharacterSlot.h"

extern Game* game;

using namespace Constants;

Battle::Battle()
{
    accumulateTimer = new QTimer();
    accumulateTimer->setSingleShot(true);
}

Battle::~Battle()
{

}

void Battle::update()
{
    if(state == BattleState::idle){
        // do nothing
    }
    else if(state == BattleState::accumulating){
        for(int i = 0; i < RuneTypeCount; i++){
            game->getCharacterSlot();
        }
    }
    else if(state == BattleState::attacking){

    }
    else if(state == BattleState::defensing){

    }
}


void Battle::start()
{
    foreach(arrangementInfo arra, arrangement){
        Enemy* e = new Enemy(arra.type);
        enemyList.push_back(e);
        e->setPos(arra.placementCord);
        game->getScene()->addItem(e);
    }
}

void Battle::end()
{
    foreach(Enemy* e, enemyList){
        game->getScene()->removeItem(e);
        e->remove();
    }
}

void Battle::triggerCountDown()
{

}

void Battle::playerAttack(attackInfo info)
{
    state = BattleState::accumulating;
    atkinfo = info;
    accumulateTimer->start(AccumulateTime);
}

void Battle::enemyAttack()
{

}

void Battle::passRound()
{

}

void Battle::setArrangement(QList<arrangementInfo> arra)
{
    arrangement = arra;
}

