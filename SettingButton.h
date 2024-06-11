#ifndef SETTINGBUTTON_H
#define SETTINGBUTTON_H

#include "Object.h"
#include "MouseListener.h"

class SettingButton: public Object{
public:
    SettingButton();
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SETTINGBUTTON_H
