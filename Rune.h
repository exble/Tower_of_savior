#ifndef RUNE_H
#define RUNE_H

#include "Object.h"
#include "enum.h"

class Rune : public Object{
public:
    Rune(RuneType type, RuneState state);
    RuneType getType() const;
    RuneState getState() const;

    void setState(RuneState newState);
    void newImage();

private:
    void update();
    RuneType type;
    RuneState state;
};

#endif // RUNE_H
