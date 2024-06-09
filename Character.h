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

private:
    CharacterType type;
    QColor color;
};

#endif // CHARACTER_H
