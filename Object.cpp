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

