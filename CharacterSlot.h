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
    const Character** getSlot() const;
    const QGraphicsTextItem** getTextSlot() const;
private:
    void update();


private:
    static const int max_slot = 6;
    static const int slot_x = 0;
    static const int slot_y = Constants::RuneAreaY - Constants::PlayerBarHeight - Constants::CharacterHeight;

    // max_slot = 6
    Character* slot[max_slot];
    QGraphicsTextItem* text_slot[max_slot];
    std::string text_string[max_slot];
    QFont font;
};

#endif // CHARACTERSLOT_H
