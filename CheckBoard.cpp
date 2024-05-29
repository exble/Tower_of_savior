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
    for(int i = 0; i < RUNE_COUNT_Y; i++){
        for(int j = 0; j < RUNE_COUNT_X; j++){
            QGraphicsRectItem* tile = new QGraphicsRectItem();
            tile->setRect(RUNE_AREA_X + j*RUNE_WIDTH, RUNE_AREA_Y + i*RUNE_HEIGHT, RUNE_WIDTH, RUNE_HEIGHT);
            if((i+j)%2){
                // bright
                color.setRgb(57, 37, 21);
            }
            else{
                // dark
                color.setRgb(30, 20, 10);
            }
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(color);
            tile->setBrush(brush);
            tile->setZValue(BOARD_Z_VALUE);
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
