#include "DamageBox.h"
#include "Game.h"
#include "Config.h"

#include <QFont>

using namespace Constants;

extern Game* game;

DamageBox::DamageBox(int value, QColor color, QPointF loc)
{
    setPlainText(std::to_string(value).c_str());
    setDefaultTextColor(color);
    QFont font;
    font.setBold(true);
    font.setPixelSize(30);

    setFont(font);
    setPos(loc);
    game->getScene()->addItem(this);

    timer = new QTimer();
    timer->setSingleShot(true);
    timer->start(DamageFloatingTime);
}

DamageBox::~DamageBox()
{
    game->getScene()->removeItem(this);
}

void DamageBox::update()
{
    if(!timer->isActive()){
        remove();
    }
    setPos(x(), y() - DamageFloatingSpeed);
    setOpacity((float)(timer->remainingTime()) / DamageFloatingTime);
}
