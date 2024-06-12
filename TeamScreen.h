#ifndef TEAMSCREEN_H
#define TEAMSCREEN_H


#include "MouseListener.h"
#include "enum.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include <QTimer>
class CharacterSlot;

class TeamScreen : public MouseListener{
public:
    TeamScreen();
    static QGraphicsScene* teamScene;
    QGraphicsPixmapItem* Teambackground = nullptr;
    QList<QGraphicsPixmapItem*> TeamMember;
    QGraphicsPixmapItem* TeamMember1 = nullptr;
    QGraphicsPixmapItem* TeamMember2 = nullptr;
    QGraphicsPixmapItem* TeamMember3 = nullptr;
    QGraphicsPixmapItem* TeamMember4 = nullptr;
    QGraphicsPixmapItem* TeamMember5 = nullptr;
    QRectF bottom;
    void AddMember(int Type);
    void removeMember(int position);
    QPixmap originalPixmap ;
    QPixmap TeamPixmap ;
    QPixmap ReadyPixmap ;
    QPixmap scaledPixmap;
    CharacterSlot* characterSlot;
    QPixmap character1 = QPixmap(":/character/dataset/character/ID1.png");
    QPixmap character2 = QPixmap(":/character/dataset/character/ID2.png");
    QPixmap character3 = QPixmap(":/character/dataset/character/ID3.png");
    QPixmap character4 = QPixmap(":/character/dataset/character/ID4.png");
    QPixmap character5 = QPixmap(":/character/dataset/character/ID5.png");
    QPixmap member1;
    QPixmap member2;
    QPixmap member3;
    QPixmap member4;
    QPixmap member5;
    QPixmap member6;
    const int Teamsize = 6;
    QList<int> member;
    QList<QPixmap> characterType{character1,character2,character3,character4,character5};

private:
    void restart_tick();
};

class TeamMouseMove : public QGraphicsRectItem{
public:
    TeamMouseMove();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};



#endif // TEAMSCREEN_H
