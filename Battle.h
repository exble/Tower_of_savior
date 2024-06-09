#ifndef BATTLE_H
#define BATTLE_H

#include "TickListener.h"
#include "enum.h"
#include "Config.h"

#include <QPoint>
#include <QTimer>

class Enemy;

class Battle: public TickListener{
public:
    Battle();
    ~Battle();
    void start();
    void end();
    void triggerCountDown();
    void playerAttack(attackInfo info);
    void enemyAttack();
    void passRound();
    void setArrangement(QList<arrangementInfo> arra);
private:
    void update();
    QList<arrangementInfo> arrangement;
    std::array<int, 6> attackOfEachSlot;
    QList<Enemy*> enemyList;
    std::string str;
    QTimer* timer = nullptr;
    QTimer* attackTimer = nullptr;
    BattleState state;
    attackInfo atkinfo;
};

#endif // BATTLE_H
