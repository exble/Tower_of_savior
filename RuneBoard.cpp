#include "RuneBoard.h"
#include "CheckBoard.h"
#include "Game.h"
#include "PlayerStatusBar.h"
#include "Battle.h"

#include <QDebug>

extern Game* game;

using namespace Constants;

RuneBoard::RuneBoard()
{
    // init rand()
    srand(time(NULL));

    // init backBoard
    backBoard = new CheckBoard();
    backBoard->placeBoard();

    // init dummy_rune
    dummy_rune = new QGraphicsPixmapItem();
    dummy_rune->setOpacity(DummyInactiveOpacity);
    dummy_rune->setZValue(100);
    game->getScene()->addItem(dummy_rune);

    state = RuneBoardState::waiting;

    // init Linking Timer
    timer = new QTimer();
    timer->setSingleShot(true);

    CountDownTimer = new QTimer();
    CountDownTimer->setSingleShot(true);

    resetBoard();


    // Initialize combo count and text item
    comboCnt = 0;
    comboTextItem = new QGraphicsTextItem();
    comboTextItem->setZValue(1000);
    comboTextItem->setDefaultTextColor(Qt::yellow);
    comboTextItem->setFont(QFont("Times New Roman", 40));
    comboTextItem->setPos(GameWidth - 100, GameHeight - 50); // Position in the bottom-right corner
    comboTextItem->setVisible(false); // Initially hide the combo text item
    game->getScene()->addItem(comboTextItem);
}

void RuneBoard::handleLinking()
{
    foreach(const QPoint& cord, clusters[linking_index]){
        atkinfo[runes[cord.x()][cord.y()]->getType()]++;
        runes[cord.x()][cord.y()]->remove();
        runes[cord.x()][cord.y()] = nullptr;
    }
    comboCnt++; // Increment combo count

    if (comboCnt > 1) { // Only show combo text if combo count is greater than 1
        comboTextItem->setHtml(QString("<span style='font-size:48px;'>%1</span> <span style='font-size:32px;'>combo!</span>").arg(comboCnt)); // Update text item
        comboTextItem->setPos(GameWidth - comboTextItem->boundingRect().width() - 10, GameHeight - comboTextItem->boundingRect().height() - 10); // Adjust position based on text size
        comboTextItem->setVisible(true); // Show the combo text item
    }
    updatePosition();
}

void RuneBoard::triggerLinking()
{
    state = RuneBoardState::linking;
    holding_rune->setOpacity(1);
    dummy_rune->setOpacity(DummyInactiveOpacity);
    holding_rune = nullptr;

    checkLink();
    makeCluster();
    timer->start(LinkingCD);

    game->getPlayerBar()->displayHp();

    atkinfo.clear();
    comboTextItem->setVisible(false); // Hide the combo text item when resetting combo count

    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            runes[i][j]->setState(RuneState::normal);
        }
    }
}


void RuneBoard::update()
{
    if(state == RuneBoardState::inactive){
        setRunesOpacity(0.5);
        comboTextItem->setVisible(false); // Hide the combo text item
    }
    else if(state == RuneBoardState::waiting){
        setRunesOpacity(1);
        clusters.clear();
        CountDownTimer->start(SpiningTime);
        comboTextItem->setVisible(false); // Hide the combo text item
    }
    else if(state == RuneBoardState::spinning){
        linking_index = 0;
        comboCnt = 0;
        // dealing countdown & update the bar
        handleSpinning();
    }
    else if(state == RuneBoardState::linking){
        if(linking_index == clusters.size()){
            if(linking_index == 0){
                state = RuneBoardState::inactive;
                for(int i = 0; i < RuneTypeCount; i++){
                    atkinfo[(RuneType)i] = atkinfo[(RuneType)i] * comboCnt * Multiplier;
                }
                game->getCurrentBattle()->playerAttack(atkinfo);
                comboTextItem->setVisible(false); // Hide the combo text item when attack is done
            }
            else{
                state = RuneBoardState::dropping;
                generateRunes();
                timer->start(LinkingCD);
            }
        }
        if(!timer->isActive()){
            handleLinking();
            linking_index++;
            timer->start(LinkingCD);
        }
    }
    else if(state == RuneBoardState::dropping){
        linking_index = 0;
        if(!timer->isActive()){
            handleDropping();
        }
    }
}

void RuneBoard::MousePressEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    QPoint index = CordToIndex(mouse_cord);
    if(state == RuneBoardState::waiting && index != QPoint(-1, -1)){
        triggerSpining(index);
    }
}

void RuneBoard::MouseReleaseEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
    if(state == RuneBoardState::spinning && holding_rune != nullptr){
        triggerLinking();
    }
}

void RuneBoard::MouseMoveEvent(const QGraphicsSceneMouseEvent *event)
{
    mouse_cord = event->pos();
}

void RuneBoard::initBoard()
{
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            runes[i][j] = getRandRune();
            game->getScene()->addItem(runes[i][j]);
        }
    }
}

void RuneBoard::generateRunes()
{
    for(int i = 0; i < RuneCountX; i++){
        for(int j = RuneCountY-1; j > 0; j--){
            if(runes[i][j] == nullptr){
                std::swap(runes[i][j], runes[i][j-1]);
            }
        }
        int k = 0;
        for(int j = RuneCountY-1; j >= 0; j--){
            if(runes[i][j] == nullptr){
                k++;
                runes[i][j] = getRandRune();
                runes[i][j]->setPos(i*RuneWidth, RuneAreaY - k*RuneHeight);
                game->getScene()->addItem(runes[i][j]);
            }
        }
    }

}

void RuneBoard::checkLink()
{
    // reset markMap
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            markMap[i][j] = false;
        }
    }
    // vertical 3 Link
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j + 2 < RuneCountY; j++){
            if(runes[i][j]->getType() == runes[i][j+1]->getType() && runes[i][j]->getType() == runes[i][j+2]->getType()){
                markMap[i][j] = true;
                markMap[i][j+1] = true;
                markMap[i][j+2] = true;
            }
        }
    }
    // horizontal 3 Link
    for(int i = 0; i + 2 < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
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
    clusters.clear();
    QList<QList<QPoint>> tmp_clusters;
    std::function<void(int, RuneType, int, int)>traverse;
    traverse = [&](int index, RuneType prev_type, int x, int y){
        if(x >= RuneCountX || y >= RuneCountY || x < 0){
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
    for(int j = 0; j < RuneCountY; j++){
        for(int i = 0; i < RuneCountX; i++){
            tmp_clusters.push_back(QList<QPoint>());
            traverse(i + j*RuneCountX, runes[i][j]->getType(), i, j);
        }
    }
    foreach(const QList<QPoint>& cluster, tmp_clusters){
        if(cluster.size() != 0){
            clusters.push_back(cluster);
        }
    }
}

void RuneBoard::updatePosition()
{
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            if(runes[i][j]){
                runes[i][j]->setPos(RuneAreaX + i*RuneWidth, RuneAreaY + j*RuneHeight);
            }
        }
    }
}

void RuneBoard::handleSpinning()
{
    if(!CountDownTimer->isActive()){
        triggerLinking();
        return;
    }
    if(holding_rune->getState() == RuneState::weathered){
        triggerLinking();
        return;
    }
    QPointF final_pos;
    QPointF rectified_mouse_cord;

    if(mouse_cord.x() - RuneAreaX < 0 ){
        final_pos.setX(RuneAreaX - RuneWidth/2);
        rectified_mouse_cord.setX(RuneAreaX);
    }
    else if (mouse_cord.x() >= GameWidth){
        final_pos.setX(GameWidth - RuneWidth/2);
        rectified_mouse_cord.setX(GameWidth - 1);
    }
    else{
        final_pos.setX(mouse_cord.x() - RuneWidth/2);
        rectified_mouse_cord.setX(mouse_cord.x());
    }

    if(mouse_cord.y() - RuneAreaY < 0 ){
        final_pos.setY(RuneAreaY - RuneHeight/2);
        rectified_mouse_cord.setY(RuneAreaY);
    }
    else if(mouse_cord.y() >= GameHeight){
        final_pos.setY(GameHeight - RuneHeight/2);
        rectified_mouse_cord.setY(GameHeight - 1);
    }
    else{
        final_pos.setY(mouse_cord.y() - RuneHeight/2);
        rectified_mouse_cord.setY(mouse_cord.y());
    }

    dummy_rune->setOpacity(DummyOpacity);
    dummy_rune->setPos(final_pos);


    QPoint rune_index = CordToIndex(holding_rune->pos());
    QPoint dummy_index = CordToIndex(rectified_mouse_cord);

    if(rune_index != dummy_index){
        if(runes[dummy_index.x()][dummy_index.y()]->getState() == RuneState::burning){
            game->setPlayerHp(game->getPlayerHp() - 30);
        }
        std::swap(runes[rune_index.x()][rune_index.y()], runes[dummy_index.x()][dummy_index.y()]);
        updatePosition();
        if(runes[rune_index.x()][rune_index.y()]->getState() == RuneState::weathered){
            triggerLinking();
        }
        if(enebleFire){
            runes[rune_index.x()][rune_index.y()]->setState(RuneState::burning);
        }
    }
}

void RuneBoard::handleDropping()
{
    bool is_finish = true;
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            Rune* rune = runes[i][j];
            if(CordToIndex(rune->pos()) != QPoint(i, j)){
                rune->setVy(rune->vy() + RuneGarvityAcceleration);
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
        timer->start(LinkingCD);
    }
}

void RuneBoard::triggerSpining(QPoint index)
{
    state = RuneBoardState::spinning;
    holding_rune = runes[index.x()][index.y()];
    holding_rune -> setOpacity(RuneOpacity);
    dummy_rune->setPixmap(holding_rune->pixmap());
    dummy_rune->setOpacity(DummyOpacity);

    game->getPlayerBar()->displayCountDown();
}

void RuneBoard::setRunesOpacity(float opacity)
{
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            runes[i][j]->setOpacity(opacity);
        }
    }
}

void RuneBoard::preLink()
{
    checkLink();
    makeCluster();
    while(clusters.size() > 0){
        foreach(QList<QPoint> points, clusters){
            foreach(QPoint p, points){
                runes[p.x()][p.y()]->remove();
                runes[p.x()][p.y()] = getRandRune();
                game->getScene()->addItem(runes[p.x()][p.y()]);
            }
        }

        checkLink();
        makeCluster();
    }

}

Rune *RuneBoard::getRune(int x, int y)
{
    assert((x >= 0 && x < RuneCountX && y >= 0 && y < RuneCountY) && "Index Out of Range");
    return runes[x][y];
}

void RuneBoard::setFire(bool sel)
{
    enebleFire = sel;
}

void RuneBoard::resetBoard()
{
    for(int i = 0; i < RuneCountX; i++){
        for(int j = 0; j < RuneCountY; j++){
            if(runes[i][j]){
                runes[i][j]->remove();
            }
        }
    }
    initBoard();
    preLink();
    updatePosition();
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
    int r = rand() % 6;
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
    case 5:
        ret = new Rune(RuneType::dark, RuneState::normal);
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
    ret.rx() = (int)(point.x() + RuneAreaX) / RuneWidth;
    ret.ry() = (int)(point.y() - RuneAreaY) / RuneHeight;
    if(ret.x() < 0 || ret.x() > RuneCountX || point.y() - RuneAreaY < 0 || ret.y() > RuneCountY){
        ret.rx() = -1;
        ret.ry() = -1;
    }
    return ret;
}

QPointF RuneBoard::IndexToCord(QPoint point)
{
    QPoint ret;
    ret.rx() = RuneAreaX + point.x()*RuneWidth;
    ret.ry() = RuneAreaY + point.y()*RuneHeight;
    return ret;
}

QTimer *RuneBoard::getCountDownTimer() const
{
    return CountDownTimer;
}




