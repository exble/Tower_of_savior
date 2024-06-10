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
    ~Enemy();
    int getHp() const;
    void minusHp(int val);
    Attribute getAttribute() const;

    int getCoolDown() const;

    void setCoolDown(int newCoolDown);
    void resetCoolDown();

    int getAtk() const;

    const QColor &getColor() const;

private:
    void update();
    void updateTextBox();
private:
    StatusBar* healthBar = nullptr;
    QGraphicsTextItem* CD_textBox = nullptr;
    MonsterType type;
    Attribute attribute;
    std::string CD_text;
    QColor color;
    int atk = 0;
    int hp = 0;
    int max_hp = 0;
    int coolDown = 0;
    int max_coolDown = 0;
};

#endif // ENEMY_H
