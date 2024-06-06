#include "StatusBar.h"
#include "Game.h"

#include <QBrush>

extern Game* game;

StatusBar::StatusBar(QRectF rect, const int full_val)
    :max_val(full_val)
{
    color = Qt::red;
    bar = new QGraphicsRectItem();
    barBoarder = new QGraphicsRectItem();
    m_x = rect.x();
    m_y = rect.y();
    game->getScene()->addItem(bar);
    game->getScene()->addItem(barBoarder);
}

void StatusBar::setLocation(int x, int y)
{
    m_x = x;
    m_y = y;
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

int StatusBar::getMaxValue() const
{
    return max_val;
}

void StatusBar::update()
{
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);

    QRectF newCriteria(m_x, m_y, ((float)current_val/max_val)*barBoarder->boundingRect().width(), barBoarder->boundingRect().height());
    bar->setRect(newCriteria);
    bar->setBrush(brush);
}
