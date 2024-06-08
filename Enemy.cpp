#include "Enemy.h"
#include "StatusBar.h"
#include "Game.h"

using namespace Constants;

extern Game* game;

Enemy::Enemy(MonsterType type)
{
    switch(type){
    case MonsterType::WaterSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/96n.png"));
        attribute = MonsterAttribute::water;
        color = Qt::cyan;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::EarthSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/100n.png"));
        attribute = MonsterAttribute::earth;
        color = Qt::green;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::FireSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/98n.png"));
        attribute = MonsterAttribute::fire;
        color = Qt::red;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::LightSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/102n.png"));
        attribute = MonsterAttribute::light;
        color = Qt::yellow;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::DarkSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/104n.png"));
        attribute = MonsterAttribute::dark;
        color = Qt::magenta;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::Duck:
        setPixmap(QPixmap(":/enemy/dataset/enemy/267n.png"));
        attribute = MonsterAttribute::earth;
        color = Qt::green;
        max_hp = 300;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::HellHound:
        setPixmap(QPixmap(":/enemy/dataset/enemy/180n.png"));
        attribute = MonsterAttribute::fire;
        color = Qt::red;
        max_hp = 700;
        max_coolDown = 3;
        atk = 400;
        break;
    }

    healthBar = new StatusBar(boundingRect().width(), HealthBarHeight, max_hp);
    healthBar->setColor(color);

    hp = max_hp;

    CD_textBox = new QGraphicsTextItem();

    QFont font;
    font.setBold(true);
    font.setPixelSize(14);
    CD_textBox->setFont(font);
    coolDown = max_coolDown;

    game->getScene()->addItem(CD_textBox);
}

void Enemy::update()
{
    updateTextBox();
    healthBar->setValue(hp);
    healthBar->setPos(this->x(), this->y() + boundingRect().height() + HealthBarHeight);
}

void Enemy::updateTextBox()
{
    CD_text = "CD " + std::to_string(coolDown);
    CD_textBox->setPlainText(CD_text.c_str());
    CD_textBox->setPos(this->x(), CDTextBoxY);
}
