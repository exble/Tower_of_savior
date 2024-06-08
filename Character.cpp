#include "Character.h"

Character::Character(CharacterType type)
    :type(type)
{
    switch(type){
    case CharacterType::Water:
        setPixmap(QPixmap(":/character/dataset/character/ID1.png"));
        break;
    case CharacterType::Fire:
        setPixmap(QPixmap(":/character/dataset/character/ID2.png"));
        break;
    case CharacterType::Earth:
        setPixmap(QPixmap(":/character/dataset/character/ID3.png"));
        break;
    case CharacterType::Light:
        setPixmap(QPixmap(":/character/dataset/character/ID4.png"));
        break;
    case CharacterType::Dark:
        setPixmap(QPixmap(":/character/dataset/character/ID5.png"));
        break;
    }
}
