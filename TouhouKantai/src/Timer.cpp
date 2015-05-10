#include "Timer.h"
using namespace std;
Timer::Timer()
{
    cout << "-----Init Timer-----" << endl;
    stop();
    frameNum = 1000 / DEFAULT_FPS;
    timeColor = { 0xFF, 0xFF, 0xFF, 255 };
    currFps = 60.0;
   _lock = SDL_CreateMutex();
    cout << "-----End Init Timer-----" << endl;
}

Timer::~Timer()
{
    cout << "-----Destroy Timer-----" << endl;
    if (_texture != NULL)
    {
        delete _texture;
    }
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
   /* bool res;
    if (SDL_LockMutex(_lock) == 0){*/
        //res = ((currTime = SDL_GetTicks()) % frameNum);
    //    SDL_UnlockMutex(_lock);
    //}
    //else{
    //    cout << "Can't get lock! Error: " << SDL_GetError()<<endl;
    //}

    return !((currTime = SDL_GetTicks()) % frameNum);
}
void Timer::start()
{
    stoped = false;
    startTime = SDL_GetTicks();
    lastTime = startTime;
    currTime = lastTime + frameNum;
    cout << "Timer start" << endl;
}

void Timer::stop()
{
    stoped = true;
    startTime = 0;
    lastTime  = 0;
    currTime  = 0;
    currFps = 60.0;
    countedFrame = 0;
    cout << "Timer stop" << endl;
}

void Timer::count()
{
    //currFps = 1.0 / (currTime - lastTime) * 1000;
    //lastTime = currTime;
    //cout << "counted frame:" << countedFrame << endl;

    countedFrame++;
    //cout << "curr time:" << countedFrame << endl;
    if (currFps > 2000000)
    {
        currFps = 0;
    }
    //if (currTime % 250 == 0)
    //renderFPS();
}
int Timer::frameNo()
{
    return countedFrame;
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
        
    _texture = new Texture("font/font.ttf", fpsString, timeColor, 18);
    SDL_Rect position = { SCREEN_WIDTH - _texture->getWidth() - 20,
                            SCREEN_HEIGHT - _texture->getHeight() - 20, 
                            _texture->getWidth(), 
                            _texture->getHeight()
                        };
    //printf("position:(%d,%d,%d,%d)\n", position.x, position.y, position.w, position.h);
    _texture->render(NULL, &position);
    delete _texture;
    _texture = NULL;

}
