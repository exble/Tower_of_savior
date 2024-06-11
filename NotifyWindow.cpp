#include "NotifyWindow.h"
#include "Config.h"
#include "Game.h"

#include <QBrush>
#include <QFont>

using namespace Constants;
extern Game* game;


Button::Button(QString text, QColor backcolor, QColor textcolor, QGraphicsRectItem* parent)
    :parent(parent)
{
    textbox = new QGraphicsTextItem();
    setRect(0, 0, ButtonWidth, ButtonHeight);
    setBrush(QBrush(backcolor));
    QFont font;
    font.setBold(true);
    font.setPixelSize(40);
    textbox->setFont(font);
    textbox->setDefaultTextColor(textcolor);
    textbox->setPlainText(text);
    textbox->setZValue(1000);
    positionCenter();
}

Button::~Button()
{
    game->getScene()->removeItem(textbox);
    delete textbox;
}

void Button::setFunction(void (Game::*newFunc)())
{
    Func = newFunc;
}

void Button::positionCenter()
{
    setPos(parent->boundingRect().center().x() - this->boundingRect().width() / 2, y());
    textbox->setPos(this->boundingRect().center().x() + x() - textbox->boundingRect().width() / 2, this->boundingRect().center().y() + y() - textbox->boundingRect().height()/2);
}

void Button::setBackGround(bool sel)
{
    setVisible(sel);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event && Func){
        (game->*Func)();
    }
}

NotifyWindow::NotifyWindow()
{
    setRect(0, 0, GameWidth, GameHeight);
    setBrush(QBrush(Qt::white));
}

void NotifyWindow::show()
{
    if(!isActive){
        game->getScene()->addItem(this);
        foreach(Button* b, buttons){
            game->getScene()->addItem(b);
            game->getScene()->addItem(b->textbox);
        }
    }

    isActive = true;
}

void NotifyWindow::hide()
{
    if(isActive){
        game->getScene()->removeItem(this);
        foreach(Button* b, buttons){
            game->getScene()->removeItem(b);
            game->getScene()->removeItem(b->textbox);
        }
    }
    isActive = false;
}

void NotifyWindow::addButton(Button *button)
{
    buttons.push_back(button);
}

bool NotifyWindow::getIsActive() const
{
    return isActive;
}
