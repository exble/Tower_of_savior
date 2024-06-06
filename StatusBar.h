#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "Object.h"
#include "TickListener.h"

#include <QGraphicsRectItem>
#include <QBrush>

class StatusBar : public TickListener{
public:
    StatusBar() = default;
    StatusBar(QRectF rect, const int full_val);
    void setLocation(int x, int y);
    void setColor(QColor);
    void setValue(int val);
    int getValue() const;
    void setMaxValue(int val);
    int getMaxValue() const;
private:
    void update();
private:
    int max_val;
    int current_val;
    int m_x, m_y;
    bool show_num;
    QGraphicsRectItem* bar;
    QGraphicsRectItem* barBoarder;
    QColor color;
    QBrush brush;
};

#endif // STATUSBAR_H
