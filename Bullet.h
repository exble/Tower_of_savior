#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "enum.h"


class Enemy;

class Bullet: public Object{
public:
    Bullet(int dmg, Attribute attribute);
    ~Bullet();
    void setTarget(QPointF target);
private:
    void update();
    void dealDamage(Enemy* enemy);
    void checkOutOfBound();
private:
    QList<QGraphicsItem*> colliders;
    QPointF target;
    QColor color;
    int dmg = 0;
    Attribute attribute;
};

#endif // BULLET_H
