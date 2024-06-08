#include "CharacterSlot.h"
#include "Character.h"
#include "Game.h"

extern Game* game;

using namespace Constants;

CharacterSlot::CharacterSlot()
{
    for(int i = 0; i < max_slot; i++){
        slot[i] = nullptr;
    }
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
}

void CharacterSlot::update()
{

}

void CharacterSlot::updatePosition()
{
    for(int i = 0; i < max_slot; i++){
        slot[i]->setPos(slot_x + i*CharacterWidth, slot_y);
    }
}
