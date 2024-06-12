#include "Bullet.h"
#include "Enemy.h"
#include "Config.h"
#include "Game.h"
#include "Battle.h"
#include "DamageBox.h"

#include <math.h>

using namespace Constants;
extern Game* game;

Bullet::Bullet(int dmg, Attribute attribute)
    :dmg(dmg), attribute(attribute)
{
    setPixmap(QPixmap(":/other/dataset/other/bullet.png"));
    game->getScene()->addItem(this);
    setZValue(100);

    switch(attribute){
    case Attribute::Water:
        color = Qt::cyan;
        break;
    case Attribute::Fire:
        color = Qt::red;
        break;
    case Attribute::Earth:
        color = Qt::green
;        break;
    case Attribute::Light:
        color = Qt::yellow;
        break;
    case Attribute::Dark:
        color = Qt::magenta;
        break;

    }
}

Bullet::~Bullet()
{

}

void Bullet::setTarget(QPointF target)
{
    this->target = target;
    QLineF line = QLineF(this->pos(), target);
    float v = line.length() / BulletupdateCount;
    setVx(v * cosf((line.angle() * PI)/180.0));
    setVy(-(v * sinf((line.angle() * PI)/180.0)));
    game->getCurrentBattle()->setBulletGoing(true);
}

void Bullet::update()
{
    colliders = collidingItems();
    Enemy* e;
    foreach(QGraphicsItem* collider, colliders){
        e = dynamic_cast<Enemy*>(collider);
        if(e != nullptr){
            dealDamage(e);
            game->getCurrentBattle()->setBulletGoing(false);
            remove();
        }
    }
    checkOutOfBound();
    move();
}

void Bullet::dealDamage(Enemy *enemy)
{
    int final_dmg = 0;
    if(attribute == Attribute::Fire && enemy->getAttribute() == Attribute::Earth){
        final_dmg = dmg*2;
    }
    else if(attribute == Attribute::Earth && enemy->getAttribute() == Attribute::Fire){
        final_dmg = dmg*0.5;
    }
    else if(attribute == Attribute::Water && enemy->getAttribute() == Attribute::Fire){
        final_dmg = dmg*2;
    }
    else if(attribute == Attribute::Fire && enemy->getAttribute() == Attribute::Water){
        final_dmg = dmg*0.5;
    }
    else if(attribute == Attribute::Earth && enemy->getAttribute() == Attribute::Water){
        final_dmg = dmg*2;
    }
    else if(attribute == Attribute::Water && enemy->getAttribute() == Attribute::Earth){
        final_dmg = dmg*0.5;
    }
    else if(attribute == Attribute::Dark && enemy->getAttribute() == Attribute::Light){
        final_dmg = dmg*2;
    }
    else if(attribute == Attribute::Light && enemy->getAttribute() == Attribute::Dark){
        final_dmg = dmg*2;
    }
    else{
        final_dmg = dmg;
    }

    db = new DamageBox(final_dmg, color, QPointF(enemy->x() + enemy->boundingRect().width()/2 - this->boundingRect().width()/2, y() - this->boundingRect().height()));

    enemy->minusHp(final_dmg);
}

void Bullet::checkOutOfBound()
{
    if(x() < 0 || x() > GameWidth || y() < 0 || y() > GameHeight){
        game->getCurrentBattle()->setBulletGoing(false);
        remove();
    }
}




