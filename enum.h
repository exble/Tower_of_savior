#ifndef ENUM_H
#define ENUM_H

enum class RuneType{
    None,
    fire,
    heart,
    light,
    water,
    earth,
    dark
};

enum class RuneState{
    None,
    normal,
    weathered,
    burning
};

enum class RuneBoardState{
    inactive,
    waiting,
    spinning,
    linking,
    dropping,
    attacking
};

enum class PlayerBarState{
    DisplayHp,
    SpinningCountDown,
};

enum class CharacterType{
    Water,
    Fire,
    Earth,
    Light,
    Dark
};

#endif // ENUM_H
