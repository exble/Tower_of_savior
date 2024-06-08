#include "PlayerStatusBar.h"
#include "Game.h"
#include "RuneBoard.h"

extern Game* game;

using namespace Constants;

const QColor PlayerStatusBar::HealthBarColor = QColor(250, 92, 100);
const QColor PlayerStatusBar::CountDownColor = QColor(179, 250, 92);


PlayerStatusBar::PlayerStatusBar()
    :StatusBar(PlayerBarWidth, PlayerBarHeight, PlayerMaxHP)
{
    setColor(HealthBarColor);
    state = PlayerBarState::DisplayHp;
    setPos(RuneAreaX, RuneAreaY - PlayerBarHeight);
    textbox = new QGraphicsTextItem();
    QFont font;
    font.setBold(true);
    font.setPixelSize(21);
    textbox->setFont(font);
    textbox->setPos(this->x()+0.8*PlayerBarWidth, this->y());
    textbox->setDefaultTextColor(Qt::white);
    game->getScene()->addItem(textbox);

    BackGround = new QGraphicsRectItem(0, 0, PlayerBarWidth, PlayerBarHeight);
    BackGround->setBrush(QBrush(Qt::black));
    BackGround->setZValue(-100);
    BackGround->setPos(this->x(), this->y());
    game->getScene()->addItem(BackGround);
}

void PlayerStatusBar::displayCountDown()
{
    state = PlayerBarState::SpinningCountDown;
    setColor(CountDownColor);
    setMaxValue(SpiningTime);
};

void PlayerStatusBar::displayHp()
{
    state = PlayerBarState::DisplayHp;
    setColor(HealthBarColor);
    setMaxValue(PlayerMaxHP);
}

void PlayerStatusBar::updateValue()
{
    if(state == PlayerBarState::DisplayHp){
        setValue(game->getPlayerHp());
    }
    else if(state == PlayerBarState::SpinningCountDown){
        setValue(game->getBoard()->getCountDownTimer()->remainingTime());
    }
}

void PlayerStatusBar::updateText()
{
    hp_status = std::to_string(game->getPlayerHp()) + '/' + std::to_string(PlayerMaxHP);
    textbox->setPlainText(hp_status.c_str());
}

void PlayerStatusBar::update()
{

    updateValue();
    updateText();
    resize();
}


