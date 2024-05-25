#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

class MouseMove;

class Game: public QObject{
    Q_OBJECT
public:
    void start();
    Game() = default;
    const QTimer &getTick() const;

private:
    QTimer tick;

private slots:
    void update();
};

#endif // GAME_H
