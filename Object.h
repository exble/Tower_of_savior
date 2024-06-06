#ifndef OBJECT_H
#define OBJECT_H

#include "Config.h"
#include "TickListener.h"

#include <QGraphicsPixmapItem>

class Object : public QGraphicsPixmapItem, public TickListener{
public:
    Object();
    virtual ~Object();
    qreal vx() const;
    qreal vy() const;
    void setVx(qreal _vx);
    void setVy(qreal _vy);
    void move();
private:
    qreal m_vx = 0, m_vy = 0;
};

#endif // OBJECT_H
