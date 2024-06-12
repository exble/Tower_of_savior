#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class TitleScreen {
public:
    TitleScreen();
    void ScreenChangetoTeam();
    static QGraphicsScene* titleScene;
    static TitleScreen* instance;
    bool distructer=0;
    enum ScreenType {Title , Team , Ready};
    ScreenType Type;
    QGraphicsPixmapItem* Titlebackground;
    QGraphicsPixmapItem* Teambackground;
    QGraphicsPixmapItem* Readybackground;
    QPixmap TitlePixmap;
    QPixmap TeamPixmap ;
    QPixmap ReadyPixmap ;
    QPixmap scaledTitlePixmap;
    QPixmap scaledTeamPixmap ;
    QPixmap scaledReadyPixmap ;

private:

};

class tsMouseMove : public QGraphicsRectItem {
public:
    tsMouseMove();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // TITLESCREEN_H
