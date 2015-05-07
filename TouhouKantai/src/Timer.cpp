#include "Timer.h"
using namespace std;
Timer::Timer(SDL_Renderer* renderer)
{
    cout << "-----Init Timer-----" << endl;
    stop();
    //frameNum = 1000 / DEFAULT_FPS;
    frameNum = 17;
    timeColor = { 0xFF, 0xFF, 0xFF, 255 };
    //position = { 200, 200, 128, 36 };
    currFps = 60.0;
    font = TTF_OpenFont("font/time_font.ttf", 18);
    //position = { 832, 684, 128, 36 };
    if (font == NULL)
    {
        cout << "font not loaded\nError: " << TTF_GetError() << endl;
        throw new exception("font not loaded");
    }
    _lock = SDL_CreateMutex();
    _renderer = renderer;
    cout << "-----End Init Timer-----" << endl;
}

Timer::~Timer()
{
    cout << "-----Destroy Timer-----" << endl;
    SDL_DestroyTexture(texture);
    cout << "-----End Destroy Timer-----" << endl;
}

bool Timer::isStopped()
{
    return stoped;
}

bool Timer::isFrame()
{
    // if current time is tick, frame is the divider of
    // current time. where the modular is 0, which means
    // it's false in C/C++
    /*bool isframe = false;
    currTime = SDL_GetTicks();
    if (currTime % frameNum == 0)
        isframe = true;*/
    bool res;
    if (SDL_LockMutex(_lock) == 0){
        res = ((currTime = SDL_GetTicks()) % frameNum);
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError()<<endl;
    }

    return res;
}
void Timer::start()
{
    stoped = false;
    startTime = SDL_GetTicks();
    lastTime = startTime;
    currTime = lastTime + frameNum;
}

void Timer::stop()
{
    stoped = true;
    startTime = 0;
    lastTime  = 0;
    currTime  = 0;
    currFps = 60.0;
    countedFrame = 0;
}

void Timer::count()
{
    //currFps = 1.0 / (currTime - lastTime) * 1000;
    //lastTime = currTime;
    countedFrame++;
    if (currFps > 2000000)
    {
        currFps = 0;
    }
    if (currTime % 250 == 0)
    currFps = countedFrame / ((currTime - startTime) / 1000.0f);
    renderFPS();
}

double Timer::getFPS()
{
    return currFps;
}
void Timer::renderFPS()
{
    string fpsString;
    ostringstream sstream;
    // change float to string && cut after two decimal numbers
    char decimalPoint = '.';
    sstream << "fps: " << currFps;
    fpsString = sstream.str();
    size_t n = fpsString.find(decimalPoint);
    if (n != string::npos && (fpsString.size() > n + 2))
    {
        fpsString[n + 3] = '\0';
        fpsString.swap(string(fpsString.c_str()));// deal with the string after \0
    }
    else if (fpsString.size() == n + 2)
    {
        fpsString[n + 2] = 0;
        fpsString[n + 3] = '\0';
        fpsString.swap(string(fpsString.c_str()));// deal with the string after \0
    }
        

    //cout << "fps string:" << fpsString << endl;

    SDL_Surface* fpsSurface = TTF_RenderText_Solid(font, fpsString.c_str(), timeColor);
    SDL_Rect position = { 960 - fpsSurface->w,
        720 - fpsSurface->h,
        fpsSurface->w,
        fpsSurface->h };
    if (fpsSurface == NULL)
    {
        cout << "Unable to create fps text data!\nError: " << TTF_GetError() << endl;
        return;
    }

    
    texture = SDL_CreateTextureFromSurface(_renderer, fpsSurface);
    SDL_RenderCopy(_renderer, texture, NULL, &position);
    //SDL_RenderCopy(_renderer, texture, NULL, NULL);
}
