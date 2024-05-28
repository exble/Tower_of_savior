#ifndef RUNE_H
#define RUNE_H

#include "Object.h"
#include "enum.h"

class Rune : public Object{
public:
    Rune(RuneType type, RuneState state);
private:
    bool is_stone;
    bool is_burning;
};

#endif // RUNE_H
