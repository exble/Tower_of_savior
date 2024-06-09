#include "Character.h"

Character::Character(CharacterType type)
    :type(type)
{
    switch(type){
    case CharacterType::Water:
        setPixmap(QPixmap(":/character/dataset/character/ID1.png"));
        attribute = Attribute::Water;
        color = Qt::cyan;
        break;
    case CharacterType::Fire:
        setPixmap(QPixmap(":/character/dataset/character/ID2.png"));
        attribute = Attribute::Fire;
        color = Qt::red;
        break;
    case CharacterType::Earth:
        setPixmap(QPixmap(":/character/dataset/character/ID3.png"));
        attribute = Attribute::Earth;
        color = Qt::green;
        break;
    case CharacterType::Light:
        setPixmap(QPixmap(":/character/dataset/character/ID4.png"));
        attribute = Attribute::Light;
        color = Qt::yellow;
        break;
    case CharacterType::Dark:
        setPixmap(QPixmap(":/character/dataset/character/ID5.png"));
        attribute = Attribute::Dark;
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

Attribute Character::getAttribute() const
{
    return attribute;
}
