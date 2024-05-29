#include "Object.h"
#include "Game.h"

#include <QDebug>
#include <typeinfo>

extern Game* game;

Object::Object()
{
    delete_flag = false;
    game->Object_list.push_back(this);

}

Object::~Object()
{
    game->Object_list.removeOne(this);
    game->getScene()->removeItem(this);
#if DEBUG_REMOVE
    qDebug() << name.c_str() << " is removed";
#endif // DEBUG_REMOVE
}

void Object::remove()
{
#if DEBUG_REMOVE
    name = typeid(*this).name();
#endif // DEBUG_REMOVE
    delete_flag = true;
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
    setPos(x() + vx(),y() + vy());
}

// this function will run for every tick
void Object::update()
{

}

void Object::update_handler()
{
    if(!delete_flag){
        update();
    }
    else{
        delete this;
    }
}

