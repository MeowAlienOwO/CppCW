#include "kbdListener.h"
using namespace std;

kbdListener::kbdListener(kbdState* states)
{
    _states = states;
    _exit = false;
}


kbdListener::~kbdListener()
{
    cout << "delete kbdListener" << endl;
}


void kbdListener::stop()
{
    cout << "exiting listener" << endl;
    _exit = true;
}

void kbdListener::start()
{
    while (!_exit)
    {
        SDL_Event e;
        cout << "listener thread running" << endl;
       /* SDL_Delay(100);
        while (SDL_PollEvent(&e) != 0)
        {
            cout << "event type"<<e.type << endl;
            if (e.type == SDL_QUIT)
            {
                _states->setExit(true);
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    _states->setExit(true);
                    break;
                case SDLK_z:
                    _states->keyDown(KEY_WATCHING_Z);
                    break;
                case SDLK_x:
                    _states->keyDown(KEY_WATCHING_X);
                    break;
                case SDLK_LSHIFT:
                    _states->keyDown(KEY_WATCHING_LSHIFT);
                    break;
                case SDLK_UP:
                    _states->keyDown(KEY_WATCHING_UP);
                    break;
                case SDLK_DOWN:
                    _states->keyDown(KEY_WATCHING_DOWN);
                    break;
                case SDLK_LEFT:
                    _states->keyDown(KEY_WATCHING_LEFT);
                    break;
                case SDLK_RIGHT:
                    _states->keyDown(KEY_WATCHING_RIGHT);
                    break;
                default:
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    _states->setExit(true);
                    break;
                case SDLK_z:
                    _states->keyUp(KEY_WATCHING_Z);
                    break;
                case SDLK_x:
                    _states->keyUp(KEY_WATCHING_X);
                    break;
                case SDLK_LSHIFT:
                    _states->keyUp(KEY_WATCHING_LSHIFT);
                    break;
                case SDLK_UP:
                    _states->keyUp(KEY_WATCHING_UP);
                    break;
                case SDLK_DOWN:
                    _states->keyUp(KEY_WATCHING_DOWN);
                    break;
                case SDLK_LEFT:
                    _states->keyUp(KEY_WATCHING_LEFT);
                    break;
                case SDLK_RIGHT:
                    _states->keyUp(KEY_WATCHING_RIGHT);
                    break;
                default:
                    break;

                }
            }
        }*/
    }

   // return 0;
}