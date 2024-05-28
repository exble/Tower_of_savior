#include "Rune.h"

Rune::Rune(RuneType type, RuneState state)
{
    switch (type) {
    case RuneType::fire:
        if(state == RuneState::normal){
            setPixmap(QPixmap(":/runestone/dataset/runestone/fire_stone.png"));
        }
        else if(state == RuneState::weathered){
            setPixmap(QPixmap(":/runestone/dataset/runestone/weathered_fire_stone.png"));
        }
        else if(state == RuneState::burning){
            setPixmap(QPixmap(":/runestone/dataset/runestone/burning_fire_stone.png"));
        }
        break;
    case RuneType::heart:
        if(state == RuneState::normal){
            setPixmap(QPixmap(":/runestone/dataset/runestone/heart_stone.png"));
        }
        else if(state == RuneState::weathered){
            setPixmap(QPixmap(":/runestone/dataset/runestone/weathered_heart_stone.png"));
        }
        else if(state == RuneState::burning){
            setPixmap(QPixmap(":/runestone/dataset/runestone/burning_heart_stone.png"));
        }
        break;
    case RuneType::light:
        if(state == RuneState::normal){
            setPixmap(QPixmap(":/runestone/dataset/runestone/light_stone.png"));
        }
        else if(state == RuneState::weathered){
            setPixmap(QPixmap(":/runestone/dataset/runestone/weathered_light_stone.png"));
        }
        else if(state == RuneState::burning){
            setPixmap(QPixmap(":/runestone/dataset/runestone/burning_light_stone.png"));
        }
        break;
    case RuneType::earth:
        if(state == RuneState::normal){
            setPixmap(QPixmap(":/runestone/dataset/runestone/earth_stone.png"));
        }
        else if(state == RuneState::weathered){
            setPixmap(QPixmap(":/runestone/dataset/runestone/weathered_earth_stone.png"));
        }
        else if(state == RuneState::burning){
            setPixmap(QPixmap(":/runestone/dataset/runestone/burning_earth_stone.png"));
        }
        break;
    case RuneType::water:
        if(state == RuneState::normal){
            setPixmap(QPixmap(":/runestone/dataset/runestone/water_stone.png"));
        }
        else if(state == RuneState::weathered){
            setPixmap(QPixmap(":/runestone/dataset/runestone/weathered_water_stone.png"));
        }
        else if(state == RuneState::burning){
            setPixmap(QPixmap(":/runestone/dataset/runestone/burning_water_stone.png"));
        }
        break;
    }
}
