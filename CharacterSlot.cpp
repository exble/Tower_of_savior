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
    }
    font.setBold(true);
}

CharacterSlot::~CharacterSlot()
{
    for(int i = 0; i < max_slot; i++){
        slot[i]->remove();
    }
}

void CharacterSlot::setCharacter(int index, CharacterType type)
{
    assert((index >= 0 || index < max_slot) && "index out of bound");
    if(slot[index] != nullptr){
        slot[index]->remove();
    }
    slot[index] = new Character(type);
    game->getScene()->addItem(slot[index]);

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
        text_slot[i]->setPos(slot_x + i*CharacterWidth, slot_y + 3);
    }
}

const Character** CharacterSlot::getSlot() const
{
    return (const Character**)slot;
}

const QGraphicsTextItem** CharacterSlot::getTextSlot() const
{
    return (const QGraphicsTextItem**)text_slot;
}
