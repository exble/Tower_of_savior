#ifndef BATTLE_H
#define BATTLE_H

#include "TickListener.h"
#include "enum.h"
#include "Config.h"

#include <QGraphicsTextItem>
#include <QPoint>
#include <QTimer>
#include <array>
#include <QGraphicsPixmapItem>

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

    void setBackgroundImagePath(const QString &path);
    QString getBackgroundImagePath() const;

    bool getEnemyAttacking() const;
    void setEnemyAttacking(bool newEnemyAttacking);
    void transformWeath();

private:
    void update();

private:
    QList<arrangementInfo> arrangement;
    std::array<int, 6> attackOfEachSlot;
    QGraphicsTextItem* healtext;
    QGraphicsTextItem* dmgtext;
    QList<Enemy*> enemyList;
    QList<Enemy*> attackList;
    QList<bool> enemyAlive;
    std::string str;
    QTimer* accumulateTimer = nullptr;
    QTimer* attackTimer = nullptr;
    QTimer* healTimer = nullptr;
    QTimer* defenseTimer = nullptr;
    bool isHealingActive = false;
    bool bulletGoing = false;
    bool enemyAttacking = false;
    BattleState state;
    attackInfo atkinfo;
    int atk_index = 0;
    int monsterIndex = 0;
    bool isFinish = false;
    QString backgroundImagePath;
};

#endif // BATTLE_H
