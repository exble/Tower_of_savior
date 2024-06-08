#ifndef CHARACTERSLOT_H
#define CHARACTERSLOT_H

#include "enum.h"
#include "Config.h"
#include "TickListener.h"

class Character;

class CharacterSlot: public TickListener{
public:
    CharacterSlot();
    ~CharacterSlot();
    void setCharacter(int index, CharacterType type);
    void updatePosition();
private:
    void update();


private:
    static const int max_slot = 6;
    static const int slot_x = 0;
    static const int slot_y = Constants::RuneAreaY - Constants::PlayerBarHeight - Constants::CharacterHeight;
    Character* slot[max_slot];
};

#endif // CHARACTERSLOT_H
