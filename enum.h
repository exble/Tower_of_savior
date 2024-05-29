#ifndef ENUM_H
#define ENUM_H

enum class RuneType{
    None,
    fire,
    heart,
    light,
    water,
    earth
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
    dropping
};

#endif // ENUM_H
