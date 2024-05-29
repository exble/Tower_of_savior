#include "Object.h"
#include "Game.h"

#include <QDebug>
#include <typeinfo>

extern Game* game;

Object::Object()
{
    game->Object_list.push_back(this);

}

Object::~Object()
{
    game->Object_list.removeOne(this);
    game->getScene()->removeItem(this);

}

qreal Object::vx() const
{
    return m_vx;
}

// Down is positive
qreal Object::vy() const
{
    return m_vy;
}

void Object::setVx(qreal _vx)
{
    m_vx = _vx;
}


// Down is positive
void Object::setVy(qreal _vy)
{
    m_vy = _vy;
}

void Object::move()
{
    setPos(x() + vx(), y() + vy());
}

