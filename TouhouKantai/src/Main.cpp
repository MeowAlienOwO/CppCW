#include "Main.h"
#include "MainMenu.h"


using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Timer* gTimer = NULL;
Stage* stage = NULL;
SDL_Thread* drawing = NULL;
SDL_mutex* kbdLock = NULL;


SDL_mutex* Texture::_lock = NULL;
SDL_Renderer* Texture::_renderer = NULL;

int main(int argc, char *argv[])
{
    if (!initialize()){
        return 1;
    }
    while (stage != nullptr)
    {
        stage->start();
        Stage* temp = stage->next();
        delete stage;
        stage = temp;
    }

    finalize();
    return 0;
}


bool initialize()
{

    cout << "-----Initializing-----" << endl;
    // initialize SDL
    cout << "-----Initializing SDL-----" << endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL not initialized!\nError: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        cout << "SDL initialize finished." << endl;
    }

    // init SDL_image
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imgFlags)) & imgFlags)
    {
        cout << "SDL_image not initialized!\nError: " << IMG_GetError() << endl;
        return false;
    }
    else
    {
        cout << "SDL_image initialize finished." << endl;
    }

    // initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf not initialized!\nError: " << TTF_GetError() << endl;
        return false;
    }

    // init SDL_mixer
     if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
     {
       cout << "SDL_mixer not initialized!\nError: " << Mix_GetError() << endl;
       return false;
     }
     else
     {
       cout << "SDL_mixer initialize finished." << endl;
     }

    cout << "-----SDL Initialized-----" << endl;
    printf("\n\n");

    cout << "-----Creating Window-----" << endl;
    // create gWindow
    gWindow = SDL_CreateWindow("Touhou Kancolle",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        return false;
    }
    else
    {
        cout << "Window initialize finished" << endl;
    }

    // init surface, texture and gRenderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    // init static field of texture
    // concurrency stuff for rendering
    Texture::setRenderer(gRenderer);
    SDL_mutex* lock = SDL_CreateMutex();
    if (lock == NULL)
    {
        cout << "lock not created!" << SDL_GetError() << endl;
        return false;
    }
    Texture::setLock(lock);

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    cout << "-----Window Created-----" << endl;
    printf("\n\n");

    // init gTimer
    gTimer = new Timer();
    gTimer->start();
    //init stage
    stage = (Stage*) new MainMenu();
    kbdLock = SDL_CreateMutex();
    
    if (kbdLock == NULL)
    {
        cout << "Can't create Lock! Error: " << SDL_GetError() << endl;
        return false;
    }


    //init drawing thread
    cout << "-----Initialize finished-----" << endl;
    return true;
}



void finalize(){
    cout << "-----Finalizing Game-----" << endl;
    //stop thread
    cout << "-----Closing Drawing Process-----" << endl;
    SDL_DestroyMutex(Texture::getLock());
    Texture::setLock(NULL);

    cout << "-----Drawing Process Closed-----" << endl;

    // free texture and render
    cout << "-----Destroying Renderer-----" << endl;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    Texture::setRenderer(NULL);

    cout << "-----Renderer Destroyed-----" << endl;

    // free gWindow
    cout << "-----Destroying Window-----" << endl;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    cout << "-----Window Destroyed-----" << endl;

    // delete timer
    cout << "-----Destroying Timer-----" << endl;
    gTimer->stop();
    delete gTimer;
    gTimer = NULL;
    cout << "-----Timer Destroyed-----" << endl;
    // close subsystems
    cout << "-----Closing Subsystem-----" << endl;
    TTF_Quit();
    cout << "TTF closed." << endl;
    Mix_Quit();
    cout << "Mix closed." << endl;
    IMG_Quit();
    cout << "IMG closed." << endl;
    SDL_Quit();
    cout << "SDL closed." << endl;
    
    cout << "-----Subsystem Closed-----" << endl;
    cout << "-----Game Closed-----" << endl;
}


int kbdListener(void* data)
{

    return 0;
}

//int draw(void* data)
//{
//    cout << endl << "-------Start drawing--------" << endl;
//    SDL_mutex* renderLock = Texture::getLock();
//    gTimer->start();
//    while (stage != nullptr)
//    {
//
//        if (gTimer->isFrame())
//        {
//                SDL_RenderClear(gRenderer);
//
//
//            if (SDL_LockMutex(stageLock) == 0)
//            {
//                if (stage != nullptr)
//                {
//                    stage->draw();
//                }
//                SDL_UnlockMutex(stageLock);
//            }
//            else
//            {
//                cout << "not able to lock mutex!Error: " << SDL_GetError() << endl;
//                gTimer->stop();
//                return -1;
//
//            }
//
//            gTimer->renderFPS();
//
//
//            SDL_RenderPresent(gRenderer);
//
//            //std::this_thread::sleep_for(std::chrono::milliseconds(1));
//            gTimer->count();
//        }
//    }
//
//    gTimer->stop();
//    cout << "-------End drawing--------" << endl;
//    return 0;
//}
//
//
