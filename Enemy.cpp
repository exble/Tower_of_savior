#include "Enemy.h"
#include "StatusBar.h"
#include "Game.h"
#include "Battle.h"

using namespace Constants;

extern Game* game;

Enemy::Enemy(MonsterType type)
    :type(type)
{
    switch(type){
    case MonsterType::WaterSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/96n.png"));
        attribute = Attribute::Water;
        color = Qt::cyan;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::EarthSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/100n.png"));
        attribute = Attribute::Earth;
        color = Qt::green;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::FireSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/98n.png"));
        attribute = Attribute::Fire;
        color = Qt::red;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::LightSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/102n.png"));
        attribute = Attribute::Light;
        color = Qt::yellow;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::DarkSlime:
        setPixmap(QPixmap(":/enemy/dataset/enemy/104n.png"));
        attribute = Attribute::Dark;
        color = Qt::magenta;
        max_hp = 100;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::Duck:
        setPixmap(QPixmap(":/enemy/dataset/enemy/267n.png"));
        attribute = Attribute::Earth;
        color = Qt::green;
        max_hp = 300;
        max_coolDown = 3;
        atk = 200;
        break;
    case MonsterType::HellHound:
        setPixmap(QPixmap(":/enemy/dataset/enemy/180n.png"));
        attribute = Attribute::Fire;
        color = Qt::red;
        max_hp = 700;
        max_coolDown = 3;
        atk = 400;
        break;
    }

    healthBar = new StatusBar(boundingRect().width(), HealthBarHeight, max_hp);
    healthBar->setColor(color);

    healthBarBackGround = new QGraphicsRectItem();
    healthBarBackGround->setBrush(QBrush(Qt::black));
    healthBarBackGround->setRect(healthBar->boundingRect());
    healthBarBackGround->setZValue(-1);
    game->getScene()->addItem(healthBarBackGround);

    hp = max_hp;

    CD_textBox = new QGraphicsTextItem();

    QFont font;
    font.setBold(true);
    font.setPixelSize(14);
    CD_textBox->setFont(font);
    CD_textBox->setDefaultTextColor(Qt::white);
    coolDown = max_coolDown;



    game->getScene()->addItem(CD_textBox);
}

Enemy::~Enemy()
{
    healthBar->remove();
    game->getScene()->removeItem(CD_textBox);
    delete CD_textBox;

    game->getScene()->removeItem(healthBarBackGround);
    delete healthBarBackGround;

    game->getCurrentBattle()->getEnemyList().removeOne(this);
}

void Enemy::update()
{
    updateTextBox();
    healthBar->setValue(hp);
    healthBar->setPos(this->x(), this->y() + boundingRect().height() + HealthBarHeight);

    healthBarBackGround->setPos(healthBar->pos());

}

void Enemy::updateTextBox()
{
    CD_text = "CD " + std::to_string(coolDown);
    CD_textBox->setPlainText(CD_text.c_str());
    CD_textBox->setPos(this->x(), CDTextBoxY);
}

MonsterType Enemy::getType() const
{
    return type;
}

const QColor &Enemy::getColor() const
{
    return color;
}

int Enemy::getAtk() const
{
    return atk;
}

void Enemy::setCoolDown(int newCoolDown)
{
    coolDown = newCoolDown;
}

void Enemy::resetCoolDown()
{
    coolDown = max_coolDown;
}

int Enemy::getCoolDown() const
{
    return coolDown;
}

Attribute Enemy::getAttribute() const
{
    return attribute;
}

int Enemy::getHp()const
{
    return hp;
}

void Enemy::minusHp(int val)
{
    hp -= val;
    if(hp < 0)
        hp = 0;
}
