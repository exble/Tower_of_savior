#ifndef PLAYERSTATUSBAR_H
#define PLAYERSTATUSBAR_H

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>

#include "StatusBar.h"
#include "enum.h"
#include "Config.h"


class PlayerStatusBar: public StatusBar{
public:
    PlayerStatusBar();
    void displayCountDown();
    void displayHp();
    void updateValue();
    void updateText();

private:
    void update();
private:
    PlayerBarState state;
    QGraphicsTextItem* textbox;
    QGraphicsRectItem* BackGround;
    std::string hp_status;
    static const QColor HealthBarColor;
    static const QColor CountDownColor;
};
#endif // PLAYERSTATUSBAR_H
