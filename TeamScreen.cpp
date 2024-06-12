#include "TitleScreen.h"
#include "TeamScreen.h"
#include "CharacterSlot.h"
#include "Character.h"
#include "Game.h"
#include "Config.h"
#include "MouseListener.h"
#include "enum.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QRect>
#include <QList>

QGraphicsScene* TeamScreen::teamScene = nullptr;


extern Game* game;

using namespace Constants;

TeamScreen::TeamScreen() {
    teamScene = new QGraphicsScene();
    Teambackground = new QGraphicsPixmapItem();


    TeamPixmap = QPixmap(":/other/dataset/other/select0.png");
    characterSlot = new CharacterSlot();

    scaledPixmap = TeamScreen::TeamPixmap.scaled(GameWidth, GameHeight, Qt::KeepAspectRatio);         //                                                                               1
    Teambackground->setPixmap(scaledPixmap); 
    Teambackground->setPos(0, 0);
    teamScene->addItem(Teambackground);

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

    //character
    TeamMember1->setPixmap(character1);
    TeamMember1->setPos(12,500);
    game->getTeamScreen()->teamScene->addItem(TeamMember1);
    TeamMember2->setPixmap(character2);
    TeamMember2->setPos(12+CharacterWidth*1.2,500);
    game->getTeamScreen()->teamScene->addItem(TeamMember2);
    TeamMember3->setPixmap(character3);
    TeamMember3->setPos(12+CharacterWidth*2.4,500);
    game->getTeamScreen()->teamScene->addItem(TeamMember3);
    TeamMember4->setPixmap(character4);
    TeamMember4->setPos(12+CharacterWidth*3.6,500);
    game->getTeamScreen()->teamScene->addItem(TeamMember4);
    TeamMember5->setPixmap(character5);
    TeamMember5->setPos(12+CharacterWidth*4.8,500);
    game->getTeamScreen()->teamScene->addItem(TeamMember5);

    QGraphicsTextItem* readyText = new QGraphicsTextItem("Ready");
    readyText->setPos(390, 780);
    QFont font = readyText->font();
    font.setPointSize(24);
    readyText->setDefaultTextColor(Qt::white);
    readyText->setFont(font);
    teamScene->addItem(readyText);
    #if DEBUG_SCREEN
        qDebug() << "TeamScreen() initialized " ;
    #endif
        for (int i = 0 ; i <  game->member.size() ; i++) {
    #if DEBUG_SCREEN
        qDebug() << "add" << game->member.size() << " " << game->member[i] << " " << TeamMember.size()<< " " << TeamMember[5];
    #endif
            AddMember(game->member[i]);
        }
}

void TeamScreen::removeMember(int position)
{
#if DEBUG_SCREEN
    qDebug() << "removeMember" ;
#endif

}

void TeamScreen::AddMember(int Type)
{
#if DEBUG_SCREEN
    qDebug() << "AddMember" ;
#endif
    game->member.push_back(Type);
    for (int i = 0 ; i <  game->member.size() ; i++) {
#if DEBUG_SCREEN
    qDebug() << "show" << game->member.size() << " " << game->TeamMember.size()<< " " << game->TeamMember[i];
#endif

        game->TeamMember[i]->setPixmap(characterType[game->member[i]-1]);
        game->TeamMember[i]->setPos(i*CharacterWidth,320);
        game->getTeamScreen()->teamScene->addItem(game->TeamMember[i]);
    }
}

TeamMouseMove::TeamMouseMove() {
    setRect(0, 0, GameWidth, GameHeight);
    TeamScreen::teamScene->addItem(this);
}

void TeamMouseMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF cord = event->pos();
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MousePressEvent(event);
    }
#if DEBUG_SCREEN
    qDebug() << "Mouse Pressed at x = " <<  cord.x() << " y = " << cord.y();
#endif
    if (cord.x() > 12 && cord.x() < 12+CharacterWidth && cord.y() > 500 && cord.y() < 500 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->AddMember(1);
    }
    else if (cord.x() > 12+CharacterWidth*1.2 && cord.x() < 12+CharacterWidth*2.2 && cord.y() > 500 && cord.y() < 500 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->AddMember(2);
    }
    else if (cord.x() > 12+CharacterWidth*2.4 && cord.x() < 12+CharacterWidth*3.4 && cord.y() > 500 && cord.y() < 500 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->AddMember(3);
    }
    else if (cord.x() > 12+CharacterWidth*3.6 && cord.x() < 12+CharacterWidth*4.6 && cord.y() > 500 && cord.y() < 500 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->AddMember(4);
    }
    else if (cord.x() > 12+CharacterWidth*4.8 && cord.x() < 12+CharacterWidth*5.8 && cord.y() > 500 && cord.y() < 500 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->AddMember(5);
    }
    if (cord.x() > 460 && cord.x() < 535 && cord.y() > 140 && cord.y() < 190 ) {
        game->member.clear();
        game->ChangeScreentoTeam();
#if DEBUG_SCREEN
    qDebug() << "Reset";
#endif
    }
    if (cord.x() > 5 && cord.x() < 74 && cord.y() > 140 && cord.y() < 190 ) {
        game->member.clear();
        game->ChangeScreentoTitle();
#if DEBUG_SCREEN
    qDebug() << "gotoTitle";
#endif
    }
    if (cord.x() > 347 && cord.x() < 534 && cord.y() > 764 && cord.y() < 842 && game->member.size() == 6) {

#if DEBUG_SCREEN
    qDebug() << "gotoReady";
#endif
        game->ChangeScreentoReady();
    }

    if (cord.x() > 0 && cord.x() < CharacterWidth && cord.y() > 310 && cord.y() < 310 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->removeMember(1);
    }
    else if (cord.x() > CharacterWidth && cord.x() < CharacterWidth*2 && cord.y() > 310 && cord.y() < 310 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->removeMember(2);
    }
    else if (cord.x() > CharacterWidth*2 && cord.x() < CharacterWidth*3 && cord.y() > 310 && cord.y() < 310 + CharacterHeight  && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {


        game->getTeamScreen()->removeMember(3);
    }
    else if (cord.x() > CharacterWidth*3 && cord.x() < CharacterWidth*4 && cord.y() > 310 && cord.y() < 310 + CharacterHeight  && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->removeMember(4);
    }
    else if (cord.x() > CharacterWidth*4 && cord.x() < 12+CharacterWidth*5 && cord.y() > 310 && cord.y() < 310 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->removeMember(5);
    }
    else if (cord.x() > CharacterWidth*5 && cord.x() < CharacterWidth*6 && cord.y() > 310 && cord.y() < 310 + CharacterHeight && game->getTeamScreen()->member.size()< game->getTeamScreen()->Teamsize) {

        game->getTeamScreen()->removeMember(6);
    }

}

void TeamMouseMove::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseReleaseEvent(event);

    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Released at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

void TeamMouseMove::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    foreach(MouseListener* listener, game->MouseListeners){
        listener->MouseMoveEvent(event);
    }
#if DEBUG_SCREEN
    QPointF cord = event->pos();
    qDebug() << "Mouse Moving at x = " <<  cord.x() << " y = " << cord.y();
#endif
}

