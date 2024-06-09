#ifndef CHARACTERSLOT_H
#define CHARACTERSLOT_H

#include "enum.h"
#include "Config.h"
#include "TickListener.h"

#include <QGraphicsTextItem>
#include <QFont>

class Character;

class CharacterSlot: public TickListener{
public:
    CharacterSlot();
    ~CharacterSlot();
    void setCharacter(int index, CharacterType type);
    void updatePosition();
    // max_slot = 6
    const std::array<Character*, 6>& getSlot() const;
    std::array<QGraphicsTextItem*, 6>& getTextSlot();
    void clearTextSlot();

private:
    void update();
private:
    static const int max_slot = 6;
    static const int slot_x = 0;
    static const int slot_y = Constants::RuneAreaY - Constants::PlayerBarHeight - Constants::CharacterHeight;

    // max_slot = 6
    std::array<Character*, max_slot> slot;
    std::array<QGraphicsTextItem*, max_slot> text_slot;
    //std::string text_string[max_slot];
    QFont font;
};

#endif // CHARACTERSLOT_H
