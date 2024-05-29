#ifndef TICKLISTENER_H
#define TICKLISTENER_H

class TickListener{
    friend class Game;
public:
    TickListener();
    virtual ~TickListener();
    virtual void update();
    void remove();
private:
    void update_handler();
    bool delete_flag = false;
#if DEBUG_REMOVE
    std::string name;
#endif // DEBUG_REMOVE
};

#endif // TICKLISTENER_H
