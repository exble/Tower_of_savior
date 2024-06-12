#include "ReadyScreen.h"
#include "TitleScreen.h"
#include "TeamScreen.h"
#include "CharacterSlot.h"
#include "Character.h"
#include "Game.h"
#include "Config.h"
#include "MouseListener.h"
#include "enum.h"
#include "RuneBoard.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QRect>
#include <QList>

QGraphicsScene* ReadyScreen::readyScene = nullptr;


extern Game* game;

using namespace Constants;

ReadyScreen::ReadyScreen() {
    readyScene = new QGraphicsScene();
    Teambackground = new QGraphicsPixmapItem();


    ReadyPixmap = QPixmap(":/other/dataset/other/select1.png");
    characterSlot = new CharacterSlot();

    scaledPixmap = ReadyScreen::ReadyPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);         //                                                                               1
    Teambackground->setPixmap(scaledPixmap);
    Teambackground->setPos(0, 0);
    readyScene->addItem(Teambackground);

    Teambackground = new QGraphicsPixmapItem();
    TeamMember = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
    TeamMember[0] = new QGraphicsPixmapItem();
    TeamMember[1] = new QGraphicsPixmapItem();
    TeamMember[2] = new QGraphicsPixmapItem();
    TeamMember[3] = new QGraphicsPixmapItem();
    TeamMember[4] = new QGraphicsPixmapItem();
    TeamMember[5] = new QGraphicsPixmapItem();
    TeamMember1 = new QGraphicsPixmapItem();
    TeamMember2 = new QGraphicsPixmapItem();
    TeamMember3 = new QGraphicsPixmapItem();
    TeamMember4 = new QGraphicsPixmapItem();
    TeamMember5 = new QGraphicsPixmapItem();
    //ShowMember();
    //character
    for (int i = 0 ; i <  game->member.size() ; i++) {
#if DEBUG_SCREEN
    qDebug() << "add" << game->member.size() << " " << game->member[i] << " " << TeamMember.size()<< " " << TeamMember[5];
#endif
        AddMember(game->member[i]);
    }

    #if DEBUG_SCREEN
        qDebug() << "ReadyScreen() initialized " ;
    #endif
}


/*const std::array<int, 6> & TeamScreen::getcharacter() const
{
    return character;
}*/

void ReadyScreen::AddMember(int Type)
{
#if DEBUG_SCREEN
    qDebug() << "AddMember" ;
#endif
    for (int i = 0 ; i <  game->member.size() ; i++) {
#if DEBUG_SCREEN
    qDebug() << "show" << game->member.size() << " " << game->TeamMember.size()<< " " << game->TeamMember[i];
#endif

        game->TeamMember[i]->setPixmap(characterType[game->member[i]-1]);
        game->TeamMember[i]->setPos(i*CharacterWidth,330);
        game->getReadyScreen()->readyScene->addItem(game->TeamMember[i]);
    }
}

void ReadyScreen::ShowMember()
{
#if DEBUG_SCREEN
    qDebug() << "ShowMember" ;
#endif

    for (int i = 0 ; i <  game->member.size() ; i++) {
#if DEBUG_SCREEN
    qDebug() << "show" << game->member.size() << " " << game->member[i];
#endif
        game->getReadyScreen()->AddMember(game->member[i]);
    }
}

ReadyMouseMove::ReadyMouseMove() {
    setRect(0, 0, GameWidth, GameHeight);
    ReadyScreen::readyScene->addItem(this);
}

void ReadyMouseMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cord = event->pos();
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MousePressEvent(event);
    }
#if DEBUG_SCREEN
    qDebug() << "Mouse Pressed at x = " <<  cord.x() << " y = " << cord.y();
#endif

    if (cord.x() > 5 && cord.x() < 70 && cord.y() > 135 && cord.y() < 200 ) {
        game->member.clear();
        game->ChangeScreentoTeam();
#if DEBUG_SCREEN
    qDebug() << "gotoTeam";
#endif
    }
    if (cord.x() > 350 && cord.x() < 540 && cord.y() > 660 && cord.y() < 750 ) {

#if DEBUG_SCREEN
    qDebug() << "End";
#endif
        game->getView()->setScene(game->getScene());
        game->getBoard()->setState(RuneBoardState::waiting);
        for(int i = 0; i < 6; i++){
            game->getCharacterSlot()->setCharacter(i,(CharacterType)(game->member[i]-1));
        }
        game->getCharacterSlot()->updatePosition();

    }
}

void ReadyMouseMove::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseReleaseEvent(event);

    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Released at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

void ReadyMouseMove::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseMoveEvent(event);
    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Moving at x = " <<  cord.x() << " y = " << cord.y();
#endif
}
