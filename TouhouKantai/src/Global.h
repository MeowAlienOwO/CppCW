#ifndef GLOBAL_H
#define GLOBAL_H

#include "Includes.h"
#include "kbdState.h"
#include "Macro.h"

extern Timer *gTimer;
extern kbdState* gKbdState;
extern SDL_Renderer* gRenderer;
extern SDL_mutex* mutex;


#endif