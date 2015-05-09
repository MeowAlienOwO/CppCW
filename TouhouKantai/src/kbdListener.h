#ifndef KBD_LISTENER_H
#define KBD_LISTENER_H

#include "Global.h"
#include "kbdState.h"
/*
 * class kbdListener
 * listen events in kbd and change state
 */


class kbdListener{
public:
    void start();
    void stop();
    kbdListener(kbdState* states);
    ~kbdListener();
private:
    volatile bool _exit;
    kbdState* _states;
};


#endif