#ifndef GLOBAL_H
#define GLOBAL_H
#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Timer.h"
#include "Texture.h"

#include "Macro.h"

extern Timer *gTimer;
extern SDL_Renderer* gRenderer;

#endif