#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include <QGraphicsRectItem>

class CheckBoard{
public:
    CheckBoard();
    ~CheckBoard();
    void placeBoard();
private:
    QList<QGraphicsRectItem*>tiles;
};

#endif // CHECKBOARD_H
