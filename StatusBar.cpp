#include "StatusBar.h"



StatusBar::StatusBar(const int full_val)
    :max_val(full_val)
{

}

void StatusBar::setRect(QRectF _rec)
{
    rec = _rec;
}

QRectF StatusBar::getRect() const
{
    return rec;
}

void StatusBar::setValue(int val)
{
    current_val = val;
}

int StatusBar::getValue() const
{
    return current_val;
}

void StatusBar::setMaxValue(int val)
{
    max_val = val;
}

int StatusBar::getMaxValue() const
{
    return max_val;
}

void StatusBar::update()
{

}
