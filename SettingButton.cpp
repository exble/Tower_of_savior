#include "SettingButton.h"
#include "Game.h"

#include <QGraphicsSceneMouseEvent>

extern Game* game;

SettingButton::SettingButton()
{
    setPixmap(QPixmap(":/other/dataset/other/SettingButton.png"));

}

void SettingButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event){
        game->showSurrender();
    }
}
