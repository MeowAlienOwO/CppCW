#ifndef STAGE_H
#define STAGE_H
#include "Global.h"
class Stage{
public:
    /* logic done in one frame */
    virtual void logic() = 0;
    /* draw for one frame */
    virtual void draw() = 0;
    /* initialize resources */
    virtual bool initialize() = 0;
    /* destroy resources*/
    virtual void finalize() = 0;
    /* entry of stage*/
    virtual void start() = 0;
    /* exit stage */
    virtual void exit() = 0;
    /* return next stage, return nullptr as termination */
    virtual Stage* next() = 0;

    //virtual ~Stage() = 0;
    
private:

};

#endif