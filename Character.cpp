#include "Character.h"

Character::Character(CharacterType type)
    :type(type)
{
    switch(type){
    case CharacterType::Water:
        setPixmap(QPixmap(":/character/dataset/character/ID1.png"));
        color = Qt::cyan;
        break;
    case CharacterType::Fire:
        setPixmap(QPixmap(":/character/dataset/character/ID2.png"));
        color = Qt::red;
        break;
    case CharacterType::Earth:
        setPixmap(QPixmap(":/character/dataset/character/ID3.png"));
        color = Qt::green;
        break;
    case CharacterType::Light:
        setPixmap(QPixmap(":/character/dataset/character/ID4.png"));
        color = Qt::yellow;
        break;
    case CharacterType::Dark:
        setPixmap(QPixmap(":/character/dataset/character/ID5.png"));
        color = Qt::magenta;
        break;
    }
}

const QColor &Character::getColor() const
{
    return color;
}

CharacterType Character::getType() const
{
    return type;
}
