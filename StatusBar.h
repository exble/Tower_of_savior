#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "Object.h"

class StatusBar : public Object{
public:
    StatusBar(const int full_val);
    void setRect(QRectF _rec);
    QRectF getRect() const;
    void setValue(int val);
    int getValue() const;
    void setMaxValue(int val);
    int getMaxValue() const;
private:
    void update();
private:
    int max_val;
    int current_val;
    bool show_num;
    QColor color;
    QRectF rec;
};

#endif // STATUSBAR_H
