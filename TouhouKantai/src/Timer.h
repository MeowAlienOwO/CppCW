#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <string>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <sstream>
#include <cstdio>
#include "Texture.h"
#include "Macro.h"
#define DEFAULT_FPS 60

class Timer{

public:
    void start();
    void stop();
    void renderFPS();
    double getFPS();
    void count();
    bool isStopped();
    int frameNo();
    bool isFrame();
    Timer();
    ~Timer();
private:

    Uint32 startTime;
    Uint32 lastTime;
    Uint32 currTime;
    Uint32 countedFrame;
    Uint32 frameNum;
    bool stoped;
    double currFps;
    SDL_Color timeColor;
    Texture* _texture;
    SDL_mutex* _lock;
};

#endif