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

enum class MonsterAttribute{
    fire,
    heart,
    light,
    water,
    earth,
    dark
};

enum class MonsterType{
    WaterSlime,
    FireSlime,
    EarthSlime,
    LightSlime,
    DarkSlime,
    Duck,
    HellHound
};

#endif // ENUM_H
