#include "StatusBar.h"
#include "Game.h"

#include <QBrush>

extern Game* game;

StatusBar::StatusBar(int width, int height, const int max_val)
    :max_val(max_val), current_val(max_val)
{
    color = Qt::red;
    bar = new QGraphicsRectItem();
    this->setRect(0, 0, width, height);
    brush.setStyle(Qt::SolidPattern);
    game->getScene()->addItem(bar);
    game->getScene()->addItem(this);
}

StatusBar::~StatusBar()
{
    delete bar;
}

void StatusBar::setColor(QColor color)
{
    this->color = color;
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

void StatusBar::resize()
{
    brush.setColor(color);
    QRectF newCriteria(0, 0, ((float)current_val/max_val)*this->boundingRect().width(), this->boundingRect().height());
    bar->setRect(newCriteria);
    bar->setPos(this->x(), this->y());
    bar->setBrush(brush);
}

int StatusBar::getMaxValue() const
{
    return max_val;
}

void StatusBar::update()
{
    resize();
}
