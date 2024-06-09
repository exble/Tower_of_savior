#include "Battle.h"
#include "Enemy.h"
#include "Game.h"
#include "CharacterSlot.h"
#include "Character.h"
#include "RuneBoard.h"

extern Game* game;

using namespace Constants;

Battle::Battle()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    attackTimer = new QTimer();
    attackTimer->setSingleShot(true);
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
        if(!timer->isActive()){
            state = BattleState::attacking;
            game->getBoard()->setState(RuneBoardState::waiting);
            attackTimer->start(AttackSepTime);
        }
        else{
            auto text_slot = game->getCharacterSlot()->getTextSlot();
            for(size_t i = 0; i < text_slot.size(); i++){
                int the_value = attackOfEachSlot[i] * ((float)(AccumulateTime - timer->remainingTime()) / AccumulateTime);
                str = std::to_string(the_value);
                text_slot[i]->setPlainText(str.c_str());
            }
        }
    }
    else if(state == BattleState::attacking){
        if(!attackTimer->isActive()){

        }
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
    //test
}

void Battle::playerAttack(attackInfo info)
{
    state = BattleState::accumulating;
    atkinfo = info;
    timer->start(AccumulateTime);
    const auto slot = game->getCharacterSlot()->getSlot();
    for(size_t i = 0; i < slot.size(); i++) {
        switch(slot[i]->getType()){
        case CharacterType::Water:
            attackOfEachSlot[i] = atkinfo[RuneType::water];
            break;
        case CharacterType::Fire:
            attackOfEachSlot[i] = atkinfo[RuneType::fire];
            break;
        case CharacterType::Earth:
            attackOfEachSlot[i] = atkinfo[RuneType::earth];
            break;
        case CharacterType::Light:
            attackOfEachSlot[i] = atkinfo[RuneType::light];
            break;
        case CharacterType::Dark:
            attackOfEachSlot[i] = atkinfo[RuneType::dark];
            break;
        }
    }

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

