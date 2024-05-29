#include "RuneBoard.h"
#include "CheckBoard.h"
#include "Game.h"

#include <QDebug>

extern Game* game;

RuneBoard::RuneBoard()
{
    srand(time(NULL));
    backBoard = new CheckBoard();
    backBoard->placeBoard();
    dummy_rune = new QGraphicsPixmapItem();
    dummy_rune->setOpacity(DUMMY_INACTIVE_OPACITY);
    game->getScene()->addItem(dummy_rune);
    initBoard();
    updatePosition();
}

void RuneBoard::update()
{
    moving();
}

void RuneBoard::MousePressEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    is_holding = true;
    QPoint index = CordToIndex(mouse_cord);
    if(index != QPoint(-1, -1)){
        holding_rune = runes[index.x()][index.y()];
        holding_rune -> setOpacity(RUNE_OPACITY);
        dummy_rune->setPixmap(holding_rune->pixmap());
        dummy_rune->setOpacity(DUMMY_OPACITY);
    }
    else{
        holding_rune = nullptr;
    }
}

void RuneBoard::MouseReleaseEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    is_holding = false;
    if(holding_rune != nullptr){
        holding_rune->setOpacity(1);
        dummy_rune->setOpacity(DUMMY_INACTIVE_OPACITY);
        holding_rune = nullptr;
    }
}

void RuneBoard::MouseMoveEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
}

void RuneBoard::initBoard()
{
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            runes[i][j] = getRandRune();
            game->getScene()->addItem(runes[i][j]);
        }
    }
}

void RuneBoard::drop()
{

}

void RuneBoard::checkLink()
{

}

void RuneBoard::updatePosition()
{
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            runes[i][j]->setPos(RUNE_AREA_X + i*RUNE_WIDTH, RUNE_AREA_Y + j*RUNE_HEIGHT);
        }
    }
}

void RuneBoard::moving()
{
    if(is_holding && holding_rune){
        QPointF final_pos;
        QPointF rectified_mouse_cord;

        if(mouse_cord.x() - RUNE_AREA_X < 0 ){
            final_pos.setX(RUNE_AREA_X - RUNE_WIDTH/2);
            rectified_mouse_cord.setX(RUNE_AREA_X);
        }
        else if (mouse_cord.x() > GAME_WIDTH){
            final_pos.setX(GAME_WIDTH - RUNE_WIDTH/2);
            rectified_mouse_cord.setX(GAME_WIDTH - 1);
        }
        else{
            final_pos.setX(mouse_cord.x() - RUNE_WIDTH/2);
            rectified_mouse_cord.setX(mouse_cord.x());
        }

        if(mouse_cord.y() - RUNE_AREA_Y < 0 ){
            final_pos.setY(RUNE_AREA_Y - RUNE_HEIGHT/2);
            rectified_mouse_cord.setY(RUNE_AREA_Y);
        }
        else if(mouse_cord.y() > GAME_HEIGHT){
            final_pos.setY(GAME_HEIGHT - RUNE_HEIGHT/2);
            rectified_mouse_cord.setY(GAME_HEIGHT);
        }
        else{
            final_pos.setY(mouse_cord.y() - RUNE_HEIGHT/2);
            rectified_mouse_cord.setY(mouse_cord.y());
        }

        dummy_rune->setOpacity(DUMMY_OPACITY);
        dummy_rune->setPos(final_pos);


        QPoint rune_index = CordToIndex(holding_rune->pos());
        QPoint dummy_index = CordToIndex(rectified_mouse_cord);

        if(rune_index != dummy_index){
            std::swap(runes[rune_index.x()][rune_index.y()], runes[dummy_index.x()][dummy_index.y()]);
            updatePosition();
        }
    }
}

Rune* RuneBoard::getRandRune()
{
    int r = rand() % 5;
    Rune* ret;
    switch (r){
    case 0:
        ret = new Rune(RuneType::fire, RuneState::normal);
        break;
    case 1:
        ret = new Rune(RuneType::heart, RuneState::normal);
        break;
    case 2:
        ret = new Rune(RuneType::water, RuneState::normal);
        break;
    case 3:
        ret = new Rune(RuneType::earth, RuneState::normal);
        break;
    case 4:
        ret = new Rune(RuneType::light, RuneState::normal);
        break;
    default:
        ret = nullptr;
        break;
    }
    if(ret != nullptr){
        ret->setZValue(0);
    }
    return ret;
}

QPoint RuneBoard::CordToIndex(QPointF point)
{
    QPoint ret;
    ret.rx() = (int)(point.x() + RUNE_AREA_X) / RUNE_WIDTH;
    ret.ry() = (int)(point.y() - RUNE_AREA_Y) / RUNE_HEIGHT;
    if(ret.x() < 0 || ret.x() > RUNE_COUNT_X || point.y() - RUNE_AREA_Y < 0 || ret.y() > RUNE_COUNT_Y){
        ret.rx() = -1;
        ret.ry() = -1;
    }
    return ret;
}
