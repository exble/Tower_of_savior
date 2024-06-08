#ifndef ENUM_H
#define ENUM_H

#include <QPoint>

enum class RuneType{
    fire,
    heart,
    light,
    water,
    earth,
    dark
};

enum class RuneState{
    normal,
    weathered,
    burning
};

enum class BattleState{
    idle,
    accumulating,
    attacking,
    defensing
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

struct arrangementInfo{
    MonsterType type;
    QPoint placementCord;
};

struct attackInfo{
    int& operator[](RuneType type){
        return data[(int)type];
    }
    void clear(){
        for(int i = 0; i < 7; i++){
            data[i] = 0;
        }
    }
private:
    int data[7] = {};
};



#endif // ENUM_H
