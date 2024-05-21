#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>

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
