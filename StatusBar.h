#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "Object.h"
#include "TickListener.h"

#include <QGraphicsRectItem>
#include <QBrush>

class StatusBar : public TickListener, public QGraphicsRectItem{
public:
    StatusBar(int width, int height, int full_val);
    ~StatusBar();
    void setColor(QColor);
    void setValue(int val);
    int getValue() const;
    void setMaxValue(int val);
    void resize();
    int getMaxValue() const;
private:
    void update();
private:
    int max_val = 0;
    int current_val = 0;
    bool show_num = false;
    QGraphicsRectItem* bar;
    QColor color;
    QBrush brush;
};

#endif // STATUSBAR_H
