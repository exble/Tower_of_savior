#ifndef OBJECT_H
#define OBJECT_H

#include "param.h"

#include <QGraphicsPixmapItem>

class Object : public QGraphicsPixmapItem{
    friend class Game;
public:
    Object();
    virtual ~Object();
    virtual void update();
    void remove();
private:
    void update_handler();
    bool delete_flag;
#if DEBUG_REMOVE
    std::string name;
#endif // DEBUG_REMOVE
};

#endif // OBJECT_H
