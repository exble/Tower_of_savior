#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include <QGraphicsRectItem>

class CheckBoard{
public:
    CheckBoard();
    ~CheckBoard();
    void placeBoard();
    void setOpacity(float opacity);
private:
    QList<QGraphicsRectItem*>tiles;
};

#endif // CHECKBOARD_H
