#ifndef CHARACTER_H
#define CHARACTER_H

#include "Object.h"
#include "enum.h"
#include "Config.h"

class Character: public Object{
public:
    Character(CharacterType type);
private:
    CharacterType type;
};

#endif // CHARACTER_H
