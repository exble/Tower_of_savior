#include "CheckBoard.h"
#include "param.h"
#include "Game.h"

#include <QColor>

extern Game* game;

CheckBoard::CheckBoard()
{
    QColor color;
    QBrush brush;
    //row major
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 6; j++){
            QGraphicsRectItem* tile = new QGraphicsRectItem();
            tile->setRect(RUNE_AREA_X + j*RUNE_WIDTH, RUNE_AREA_Y + i*RUNE_HEIGHT, RUNE_WIDTH, RUNE_HEIGHT);
            if((i+j)%2){
                // dark
                color.setRgb(30, 20, 10);
            }
            else{
                // bright
                color.setRgb(57, 37, 21);
            }
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(color);
            tile->setBrush(brush);
            tile->setZValue(-100);
            tiles.push_back(tile);
        }
    }

}

void CheckBoard::placeBoard()
{
    foreach(QGraphicsRectItem* tile, tiles){
        game->getScene()->addItem(tile);
    }
}
