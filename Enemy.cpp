#include "Enemy.h"
#include "StatusBar.h"

using namespace Constants;

Enemy::Enemy(MonsterType type)
{
    QColor color;
    switch(type){
    case MonsterType::WaterSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/96n.png"));
        attribute = MonsterAttribute::water;
        color = Qt::cyan;
        max_hp = 100;
        atk = 200;
        break;
    case MonsterType::EarthSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/100n.png"));
        attribute = MonsterAttribute::earth;
        color = Qt::green;
        max_hp = 100;
        atk = 200;
        break;
    case MonsterType::FireSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/98n.png"));
        attribute = MonsterAttribute::fire;
        color = Qt::red;
        max_hp = 100;
        atk = 200;
        break;
    case MonsterType::LightSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/102n.png"));
        attribute = MonsterAttribute::light;
        color = Qt::yellow;
        max_hp = 100;
        atk = 200;
        break;
    case MonsterType::DarkSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/104n.png"));
        attribute = MonsterAttribute::dark;
        color = Qt::magenta;
        max_hp = 100;
        atk = 200;
        break;
    case MonsterType::Duck:
        setPixmap(QPixmap(":/enemy/dataset/enemy/267n.png"));
        attribute = MonsterAttribute::earth;
        color = Qt::green;
        max_hp = 300;
        atk = 200;
        break;
    case MonsterType::HellHound:
        setPixmap(QPixmap(":/enemy/dataset/enemy/180n.png"));
        attribute = MonsterAttribute::fire;
        color = Qt::red;
        max_hp = 700;
        atk = 400;
        break;
    }

    healthBar = new StatusBar(boundingRect().width(), HealthBarHeight, max_hp);
    healthBar->setColor(color);

    hp = max_hp;

    CD_textBox = new QGraphicsTextItem();
    CD_textBox->setPos(this->x(), CDTextBoxY);
}

void Enemy::update()
{
    healthBar->setValue(hp);
    healthBar->setPos(this->x(), this->y() + boundingRect().height() + HealthBarHeight);
}
