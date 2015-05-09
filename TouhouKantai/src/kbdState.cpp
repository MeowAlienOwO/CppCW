#include "kbdState.h"
using namespace std;
kbdState::kbdState()
{
    _lock = SDL_CreateMutex();
    if (_lock == NULL)
    {
        cout << "can't create lock!" << endl;
    }
    _exit = false;
    for (int i = 0; i < KEY_WATCHING_COUNT; i++)
    {
        _states[i] = false;
    }
}

kbdState::~kbdState()
{
    SDL_DestroyMutex(_lock);
}



void kbdState::keyUp(int key)
{
    //if (SDL_LockMutex(_lock) == 0)
    //{
        _states[key] = false;
        cout << "keyUp!" << endl;
    //    SDL_UnlockMutex(_lock);
    //}
    //else
    //{
    //    cout << "can't get lock!Error: " << SDL_GetError() << endl;
    //}
}

void kbdState::keyDown(int key)
{
    //if (SDL_LockMutex(_lock) == 0)
    //{
        cout << "keyDown!" << endl;
        _states[key] = true;
    //    SDL_UnlockMutex(_lock);
    //}
    //else
    //{
    //    cout << "can't get lock!Error: " << SDL_GetError() << endl;
    //}
    //
}


bool kbdState::getKeyState(int key)
{
    bool state = false;
  /*  if (SDL_LockMutex(_lock) == 0)
    {*/
        state = _states[key];
/*        SDL_UnlockMutex(_lock);
    }
    else
    {
        cout << "can't get lock!Error: " << SDL_GetError() << endl;
    }
 */
        return state;
}

void kbdState::setExit(bool exit)
{
    _exit = exit;
}

bool kbdState::isExit()
{
//    bool exit = _exit;
    return _exit;
}