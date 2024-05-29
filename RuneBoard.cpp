#include "RuneBoard.h"
#include "CheckBoard.h"
#include "Game.h"

#include <QDebug>

extern Game* game;

RuneBoard::RuneBoard()
{
    // init rand()
    srand(time(NULL));

    // init backBoard
    backBoard = new CheckBoard();
    backBoard->placeBoard();

    // init dummy_rune
    dummy_rune = new QGraphicsPixmapItem();
    dummy_rune->setOpacity(DUMMY_INACTIVE_OPACITY);
    dummy_rune->setZValue(100);
    game->getScene()->addItem(dummy_rune);

    state = RuneBoardState::waiting;

    // init Linking Timer
    timer = new QTimer();
    timer->setSingleShot(true);

    initBoard();
    updatePosition();
}

void RuneBoard::update()
{
    if(state == RuneBoardState::inactive){

    }
    else if(state == RuneBoardState::waiting){
        clusters.clear();
    }
    else if(state == RuneBoardState::spinning){
        linking_index = 0;
        handle_spinning();
    }
    else if(state == RuneBoardState::linking){
        if(linking_index == clusters.size()){
            if(linking_index == 0){
                state = RuneBoardState::waiting;
            }
            else{
                state = RuneBoardState::dropping;
                generateRunes();
                timer->start(LINKING_CD);
            }
        }
        if(!timer->isActive()){
            handle_linking();
            linking_index++;
            timer->start(LINKING_CD);
        }
    }
    else if(state == RuneBoardState::dropping){
        linking_index = 0;
        if(!timer->isActive()){
            handle_dropping();
        }
    }
}

void RuneBoard::MousePressEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    QPoint index = CordToIndex(mouse_cord);
    if(state == RuneBoardState::waiting && index != QPoint(-1, -1)){
        state = RuneBoardState::spinning;
        holding_rune = runes[index.x()][index.y()];
        holding_rune -> setOpacity(RUNE_OPACITY);
        dummy_rune->setPixmap(holding_rune->pixmap());
        dummy_rune->setOpacity(DUMMY_OPACITY);
    }
}

void RuneBoard::MouseReleaseEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    if(state == RuneBoardState::spinning && holding_rune != nullptr){
        state = RuneBoardState::linking;
        holding_rune->setOpacity(1);
        dummy_rune->setOpacity(DUMMY_INACTIVE_OPACITY);
        holding_rune = nullptr;

        checkLink();
        makeCluster();
        timer->start(LINKING_CD);
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

void RuneBoard::generateRunes()
{
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = RUNE_COUNT_Y-1; j > 0; j--){
            if(runes[i][j] == nullptr){
                std::swap(runes[i][j], runes[i][j-1]);
            }
        }
        int k = 0;
        for(int j = RUNE_COUNT_Y-1; j >= 0; j--){
            if(runes[i][j] == nullptr){
                k++;
                runes[i][j] = getRandRune();
                runes[i][j]->setPos(i*RUNE_WIDTH, RUNE_AREA_Y - k*RUNE_HEIGHT);
                game->getScene()->addItem(runes[i][j]);
            }
        }
    }

}

void RuneBoard::checkLink()
{
    // reset markMap
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            markMap[i][j] = false;
        }
    }
    // vertical 3 Link
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j + 2 < RUNE_COUNT_Y; j++){
            if(runes[i][j]->getType() == runes[i][j+1]->getType() && runes[i][j]->getType() == runes[i][j+2]->getType()){
                markMap[i][j] = true;
                markMap[i][j+1] = true;
                markMap[i][j+2] = true;
            }
        }
    }
    // horizontal 3 Link
    for(int i = 0; i + 2 < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            if(runes[i][j]->getType() == runes[i+1][j]->getType() && runes[i][j]->getType() == runes[i+2][j]->getType()){
                markMap[i][j] = true;
                markMap[i+1][j] = true;
                markMap[i+2][j] = true;
            }
        }
    }
}

void RuneBoard::makeCluster()
{
    QList<QList<QPoint>> tmp_clusters;
    std::function<void(int, RuneType, int, int)>traverse;
    traverse = [&](int index, RuneType prev_type, int x, int y){
        if(x >= RUNE_COUNT_X || y >= RUNE_COUNT_Y || x < 0){
            return;
        }
        if(!markMap[x][y] || runes[x][y]->getType() != prev_type){
            return;
        }
        markMap[x][y] = false;
        tmp_clusters[index].push_back(QPoint(x, y));
        traverse(index, prev_type, x+1, y);
        traverse(index, prev_type, x, y+1);
        traverse(index, prev_type, x-1, y);
    };
    for(int j = 0; j < RUNE_COUNT_Y; j++){
        for(int i = 0; i < RUNE_COUNT_X; i++){
            tmp_clusters.push_back(QList<QPoint>());
            traverse(i + j*RUNE_COUNT_X, runes[i][j]->getType(), i, j);
        }
    }
    foreach(const QList<QPoint>& cluster, tmp_clusters){
        if(cluster.size() != 0){
            clusters.push_back(cluster);
        }
    }
    qDebug() << "Number of cluster is " << clusters.size();
}

void RuneBoard::updatePosition()
{
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            if(runes[i][j]){
                runes[i][j]->setPos(RUNE_AREA_X + i*RUNE_WIDTH, RUNE_AREA_Y + j*RUNE_HEIGHT);
            }
            else{
                qDebug() << "Sanity check1";
            }
        }
    }
}

void RuneBoard::handle_spinning()
{

    QPointF final_pos;
    QPointF rectified_mouse_cord;

    if(mouse_cord.x() - RUNE_AREA_X < 0 ){
        final_pos.setX(RUNE_AREA_X - RUNE_WIDTH/2);
        rectified_mouse_cord.setX(RUNE_AREA_X);
    }
    else if (mouse_cord.x() >= GAME_WIDTH){
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
    else if(mouse_cord.y() >= GAME_HEIGHT){
        final_pos.setY(GAME_HEIGHT - RUNE_HEIGHT/2);
        rectified_mouse_cord.setY(GAME_HEIGHT - 1);
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

void RuneBoard::handle_linking()
{
    foreach(const QPoint& cord, clusters[linking_index]){
        runes[cord.x()][cord.y()]->remove();
        runes[cord.x()][cord.y()] = nullptr;
    }
    updatePosition();
}

void RuneBoard::handle_dropping()
{
    bool is_finish = true;
    for(int i = 0; i < RUNE_COUNT_X; i++){
        for(int j = 0; j < RUNE_COUNT_Y; j++){
            Rune* rune = runes[i][j];
            if(CordToIndex(rune->pos()) != QPoint(i, j)){
                rune->setVy(rune->vy() + RUNE_GRAVITY_ACCELERATION);
                is_finish = false;
            }
            else{
                rune->setVy(0);
                rune->setPos(IndexToCord(QPoint(i, j)));
            }
        }
    }
    if(is_finish){
        state = RuneBoardState::linking;
        clusters.clear();
        checkLink();
        makeCluster();
        timer->start(LINKING_CD);
    }
}

void RuneBoard::setState(RuneBoardState _state)
{
    state = _state;
}

RuneBoardState RuneBoard::getState() const
{
    return state;
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
    else{
        qDebug() << "Sanity check0";
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

QPointF RuneBoard::IndexToCord(QPoint point)
{
    QPoint ret;
    ret.rx() = RUNE_AREA_X + point.x()*RUNE_WIDTH;
    ret.ry() = RUNE_AREA_Y + point.y()*RUNE_HEIGHT;
    return ret;
}
