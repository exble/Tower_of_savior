#ifndef DAMAGEBOX_H
#define DAMAGEBOX_H

#include "TickListener.h"

#include <QGraphicsTextItem>

class DamageBox: public QGraphicsTextItem, public TickListener{
public:
    DamageBox(int value, QColor color, QPointF loc);
    ~DamageBox();
private:
    void update();
private:
    QTimer* timer;
};

#endif // DAMAGEBOX_H
