#include "CheckBoard.h"
#include "Config.h"
#include "Game.h"

#include <QColor>

extern Game* game;

using namespace Constants;

CheckBoard::CheckBoard()
{
    QColor color;
    QBrush brush;
    //row major
    for(int i = 0; i < RuneCountY; i++){
        for(int j = 0; j < RuneCountX; j++){
            QGraphicsRectItem* tile = new QGraphicsRectItem();
            tile->setRect(RuneAreaX + j*RuneWidth, RuneAreaY + i*RuneHeight, RuneWidth, RuneHeight);
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
            tile->setZValue(BoardZValue);
            tiles.push_back(tile);
        }
    }

}

CheckBoard::~CheckBoard()
{
    foreach(QGraphicsRectItem* tile, tiles){
        delete tile;
    }
}

void CheckBoard::placeBoard()
{
    foreach(QGraphicsRectItem* tile, tiles){
        game->getScene()->addItem(tile);
    }
}
