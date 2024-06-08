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
    void setArrangement(QList<arrangementInfo>);
private:
    void update();
    QList<arrangementInfo> arrangement;
    QList<Enemy*> enemyList;
    QTimer* accumulateTimer;
    BattleState state;
    attackInfo atkinfo;
};

#endif // BATTLE_H
