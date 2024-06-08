#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"
#include "enum.h"
#include "Config.h"

#include <QGraphicsTextItem>

class StatusBar;

class Enemy: public Object{
public:
    Enemy(MonsterType type);
private:
    void update();
private:
    StatusBar* healthBar;
    QGraphicsTextItem* CD_textBox;
    MonsterType type;
    MonsterAttribute attribute;
    int atk;
    int hp;
    int max_hp;
    int coolDown;
};

#endif // ENEMY_H
