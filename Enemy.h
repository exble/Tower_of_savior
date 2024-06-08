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
    void updateTextBox();
private:
    StatusBar* healthBar;
    QGraphicsTextItem* CD_textBox;
    MonsterType type;
    MonsterAttribute attribute;
    std::string CD_text;
    QColor color;
    int atk;
    int hp;
    int max_hp;
    int coolDown;
    int max_coolDown;
};

#endif // ENEMY_H
