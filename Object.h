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
    qreal vx() const;
    qreal vy() const;
    void setVx(qreal _vx);
    void setVy(qreal _vy);
    void move();
private:
    void update_handler();
private:
    bool delete_flag;
    qreal m_vx = 0, m_vy = 0;
#if DEBUG_REMOVE
    std::string name;
#endif // DEBUG_REMOVE
};

#endif // OBJECT_H
