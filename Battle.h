#ifndef BATTLE_H
#define BATTLE_H

#include "TickListener.h"
#include "enum.h"
#include "Config.h"

#include <QPoint>
#include <QTimer>
#include <array>

class Enemy;

class Battle: public TickListener{
public:
    Battle();
    ~Battle();
    void start();
    void end();
    void triggerCountDown();
    void playerAttack(attackInfo info);
    void setArrangement(QList<arrangementInfo> arra);
    void fireBullet(int index, Enemy* target, int dmg, Attribute attrbute);
    bool getBulletGoing() const;
    void setBulletGoing(bool newBulletGoing);
    void setEnemyAlive(int index, bool newdead);
    QList<Enemy *> &getEnemyList();

    bool getIsFinish() const;
    void setIsFinish(bool newIsFinish);

private:
    void update();
private:
    QList<arrangementInfo> arrangement;
    std::array<int, 6> attackOfEachSlot;
    QList<Enemy*> enemyList;
    QList<bool> enemyAlive;
    std::string str;
    QTimer* timer = nullptr;
    QTimer* attackTimer = nullptr;
    bool bulletGoing = false;
    BattleState state;
    attackInfo atkinfo;
    int atk_index = 0;
    bool isFinish = false;
};

#endif // BATTLE_H
