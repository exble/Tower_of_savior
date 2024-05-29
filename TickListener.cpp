#include "TickListener.h"
#include "Game.h"

extern Game* game;

TickListener::TickListener()
{
    game->TickListeners.push_back(this);
}

TickListener::~TickListener()
{
    game->TickListeners.removeOne(this);
#if DEBUG_REMOVE
    qDebug() << name.c_str() << " is removed";
#endif // DEBUG_REMOVE
}

void TickListener::update()
{

}

void TickListener::remove()
{
    delete_flag = true;
#if DEBUG_REMOVE
    name = typeid(*this).name();
#endif // DEBUG_REMOVE
}

void TickListener::update_handler()
{
    if(!delete_flag){
        update();
    }
    else{
        delete this;
    }
}
