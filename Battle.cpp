#include "Battle.h"
#include "Enemy.h"
#include "Game.h"
#include "CharacterSlot.h"
#include "Character.h"
#include "RuneBoard.h"
#include "Bullet.h"

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
        foreach(Enemy* e, enemyList){
            if(e->getHp() <= 0){
                e->remove();
            }
        }
    }
    else if(state == BattleState::accumulating){
        if(!timer->isActive()){
            state = BattleState::healing;
            atk_index = 0;
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
    else if(state == BattleState::healing){
        // need animation

        game->ref_playerHp() += atkinfo[RuneType::heart] * 5;
        if(game->ref_playerHp() > PlayerMaxHP){
            game->ref_playerHp() = PlayerMaxHP;
        }
        state = BattleState::attacking;
    }
    else if(state == BattleState::attacking){
        if(atk_index == 6){
            state = BattleState::defending;
            for(auto& i : enemyList){
                if(i->getCoolDown() > 0){
                    i->setCoolDown(i->getCoolDown()-1);
                }
            }
            game->getCharacterSlot()->clearTextSlot();
        }
        else if(!bulletGoing){
            if(attackOfEachSlot[atk_index] != 0){

                int r = rand() % enemyList.size();
                while (enemyList[r]->getHp() <= 0) {
                    r = rand() % enemyList.size();
                    bool allNoHpFlag = true;
                    foreach(Enemy* e, enemyList){
                        if(e->getHp() > 0){
                            allNoHpFlag = false;
                        }
                    }
                    if(allNoHpFlag){
                        break;
                    }
                }
                fireBullet(atk_index,
                           enemyList[r],
                           attackOfEachSlot[atk_index],
                           game->getCharacterSlot()->getSlot()[atk_index]->getAttribute());
            }
            atk_index++;
        }
    }

    else if(state == BattleState::defending){
        // need animation
        for(auto& i : enemyList){
            if(i->getCoolDown() == 0){
                game->ref_playerHp() -= i->getAtk();
                i->resetCoolDown();
            }
        }
        state = BattleState::idle;
    }
}

bool Battle::getIsFinish() const
{
    return isFinish;
}

void Battle::setIsFinish(bool newIsFinish)
{
    isFinish = newIsFinish;
}

QList<Enemy *> &Battle::getEnemyList()
{
    return enemyList;
}

bool Battle::getBulletGoing() const
{
    return bulletGoing;
}

void Battle::setBulletGoing(bool newBulletGoing)
{
    bulletGoing = newBulletGoing;
}

void Battle::setEnemyAlive(int index, bool newdead)
{
    enemyAlive[index] = newdead;
}


void Battle::start()
{
    foreach(arrangementInfo arra, arrangement){
        Enemy* e = new Enemy(arra.type);
        enemyList.push_back(e);
        e->setPos(arra.placementCord);
        game->getScene()->addItem(e);
        enemyAlive.push_back(true);
    }
}

void Battle::end()
{

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

void Battle::setArrangement(QList<arrangementInfo> arra)
{
    arrangement = arra;
}

void Battle::fireBullet(int index, Enemy *target, int dmg, Attribute attribute)
{
    QPointF startloc = game->getCharacterSlot()->getSlot()[index]->pos();
    startloc.setX(startloc.x() + CharacterWidth / 2);
    startloc.setY(startloc.y() + CharacterHeight / 2);
    Bullet* bullet = new Bullet(dmg, attribute);
    QPointF endloc = QPointF(target->x() + target->boundingRect().width()/2, target->y() + target->boundingRect().height()/2);
    bullet->setPos(startloc);
    bullet->setTarget(endloc);
}


