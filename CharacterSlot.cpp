#include "CharacterSlot.h"
#include "Character.h"
#include "Game.h"

extern Game* game;

using namespace Constants;

CharacterSlot::CharacterSlot()
{
    for(int i = 0; i < max_slot; i++){
        slot[i] = nullptr;
        text_slot[i] = new QGraphicsTextItem();
        text_slot[i]->setZValue(500);
    }
    font.setBold(true);
    font.setPixelSize(40);
}

CharacterSlot::~CharacterSlot()
{
    for(int i = 0; i < max_slot; i++){
        slot[i]->remove();
    }
}

void CharacterSlot::setCharacter(int index, CharacterType type)
{
    assert((index >= 0 && index < max_slot) && "index out of bound");
    if(slot[index] != nullptr){
        slot[index]->remove();
    }
    slot[index] = new Character(type);
    game->getScene()->addItem(slot[index]);
    game->getScene()->addItem(text_slot[index]);
    text_slot[index]->setDefaultTextColor(slot[index]->getColor());
    text_slot[index]->setFont(font);
}

void CharacterSlot::update()
{

}

void CharacterSlot::updatePosition()
{
    for(int i = 0; i < max_slot; i++){
        slot[i]->setPos(slot_x + i*CharacterWidth, slot_y);
        text_slot[i]->setPos(slot[i]->x() + slot[i]->boundingRect().center().x() - text_slot[i]->boundingRect().x()/2, slot_y + 20);
    }
}

const std::array<Character *, 6> &CharacterSlot::getSlot() const
{
    return slot;
}

std::array<QGraphicsTextItem *, 6> &CharacterSlot::getTextSlot()
{
    return text_slot;
}

void CharacterSlot::clearTextSlot()
{
    for(auto& i : text_slot){
        i->setPlainText("");
    }
}


