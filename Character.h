#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"
#include "enum.h"
#include "Config.h"

class Character: public Object{
public:
    Character(CharacterType type);
    const QColor &getColor() const;

    CharacterType getType() const;

    Attribute getAttribute() const;

private:
    CharacterType type;
    Attribute attribute;
    QColor color;
};

#endif // CHARACTER_H
