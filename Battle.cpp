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
    accumulateTimer = new QTimer();
    accumulateTimer->setSingleShot(true);
    attackTimer = new QTimer();
    attackTimer->setSingleShot(true);
    healTimer = new QTimer();
    healTimer->setSingleShot(true);
    defenseTimer = new QTimer();
    defenseTimer->setSingleShot(true);

    healtext = new QGraphicsTextItem();
    healtext->setPos(GameWidth/2 - 50, RuneAreaY - PlayerBarHeight);
    healtext->setDefaultTextColor(Qt::green);
    QFont font;
    font.setBold(true);
    font.setPixelSize(22);
    healtext->setFont(font);
    healtext->setZValue(500);

    dmgtext = new QGraphicsTextItem();
    dmgtext->setPos(GameWidth/2 - 50, RuneAreaY - PlayerBarHeight);
    dmgtext->setDefaultTextColor(Qt::red);
    dmgtext->setFont(font);

    state = BattleState::idle;

    game->getScene()->addItem(healtext);
    game->getScene()->addItem(dmgtext);
}

Battle::~Battle()
{

}

void Battle::update()
{
    if(state == BattleState::idle){
        foreach(Enemy* e, enemyList){

            if(e->getType() == MonsterType::HellHound && e->getHp() != 0){
                game->getBoard()->setFire(true);
            }
            else{
                game->getBoard()->setFire(false);
            }
        }

    }
    else if(state == BattleState::accumulating){
        if(!accumulateTimer->isActive()){
            state = BattleState::healing;
            atk_index = 0;
            monsterIndex = 0;
            game->getBoard()->setState(RuneBoardState::inactive);
            attackTimer->start(AttackSepTime);
        }
        else{
            auto text_slot = game->getCharacterSlot()->getTextSlot();
            auto slot = game->getCharacterSlot()->getSlot();
            for(size_t i = 0; i < text_slot.size(); i++){
                int the_value = attackOfEachSlot[i] * ((float)(AccumulateTime - accumulateTimer->remainingTime()) / AccumulateTime);
                str = std::to_string(the_value);
                text_slot[i]->setPlainText(str.c_str());
                text_slot[i]->setX(slot[i]->x() + slot[i]->boundingRect().width()/2 - text_slot[i]->boundingRect().width()/2);
            }
        }
    }
    else if(state == BattleState::healing){
        // need animation
        if(atkinfo[RuneType::heart] == 0){
            state = BattleState::attacking;
        }
        else if(!healTimer->isActive() && !isHealingActive){
            healTimer->start(Healingdelay);
            isHealingActive = true;
            game->setPlayerHp(game->getPlayerHp() + atkinfo[RuneType::heart] * 5) ;
            healtext->setVisible(true);
            healtext->setPlainText(("+" + std::to_string(atkinfo[RuneType::heart] * 5)).c_str());
        }
        else if(!healTimer->isActive() && isHealingActive){
            state = BattleState::attacking;
            isHealingActive = false;
            healtext->setVisible(false);
        }

    }
    else if(state == BattleState::attacking){
        if(atk_index == 6 && !bulletGoing){
            state = BattleState::defending;
            for(auto& i : enemyList){
                if(i->getCoolDown() > 0){
                    i->setCoolDown(i->getCoolDown()-1);
                }
            }
            game->getCharacterSlot()->clearTextSlot();

            attackList.clear();

            foreach(Enemy* e, enemyList){
                if(e->getHp() <= 0){
                    e->remove();
                }
                else{
                    attackList.push_back(e);
                }
            }
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

        if(monsterIndex == attackList.size() && !enemyAttacking){
            foreach(Enemy* e, enemyList){
                if(e->getType() == MonsterType::Duck){
                    transformWeath();
                    transformWeath();
                }
            }
            state = BattleState::idle;

            game->getBoard()->setState(RuneBoardState::waiting);
        }
        else if (!enemyAttacking){
            if(attackList[monsterIndex]->getCoolDown() == 0){
                attackList[monsterIndex]->attack();
                enemyAttacking = true;
            }
            monsterIndex++;
        }
    }
}

void Battle::transformWeath()
{
    std::vector<QPoint> normalList;
    // all weathered check
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            if(game->getBoard()->getRune(i, j)->getState() == RuneState::normal){
                normalList.push_back(QPoint(i, j));
                break;
            }
        }
    }
    if(normalList.size() == 0){
        return;
    }
    int r = rand() % normalList.size();
    game->getBoard()->getRune(normalList[r].x(), normalList[r].y())->setState(RuneState::weathered);
}

bool Battle::getEnemyAttacking() const
{
    return enemyAttacking;
}

void Battle::setEnemyAttacking(bool newEnemyAttacking)
{
    enemyAttacking = newEnemyAttacking;
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
    game->setBackgroundImage(backgroundImagePath); // Set the background image
}

void Battle::end()
{
    foreach(Enemy* e, enemyList){
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
    accumulateTimer->start(AccumulateTime);
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

void Battle::setBackgroundImagePath(const QString &path)
{
    backgroundImagePath = path;
}

QString Battle::getBackgroundImagePath() const
{
    return backgroundImagePath;
}
