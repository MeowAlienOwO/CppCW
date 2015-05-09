#include "Main.h"
#include "MainMenu.h"
#include "Stage.h"
using namespace std;

MainMenu::MainMenu()
{
    initialize();
}
MainMenu::~MainMenu()
{
    finalize();
}

void MainMenu::logic()
{

    // deal with key presses
    //if (gKbdState->getKeyState(KEY_WATCHING_UP))
    //{
    //    _choice = ++_choice % ENTRY_NUM;
    //    Mix_PlayChannel(-1, _ok, 0);

    //}
    //else if (gKbdState->getKeyState(KEY_WATCHING_DOWN))
    //{
    //    _choice = --_choice < 0 ? _choice = ENTRY_NUM - 1 : _choice;
    //    Mix_PlayChannel(-1, _ok, 0);

    //}
    //else if (gKbdState->getKeyState(KEY_WATCHING_Z))
    //{
    //    Mix_PlayChannel(-1, _ok, 0);
    //    _exit = true;
    //}
    //else if (gKbdState->getKeyState(KEY_WATCHING_X))
    //{
    //    cout << "cancel" << endl;
    //    Mix_PlayChannel(-1, _cancel, 0);
    //    _choice = ENTRY_NUM - 1;
    //}




    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            _exit = true;
        }
        else if (e.type == SDL_KEYDOWN){

            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                // key up
                _choice = ++_choice % ENTRY_NUM;
                Mix_PlayChannel(-1, _ok, 0);
                cout << _choice << endl;
                   break;
            case SDLK_DOWN:
                cout << _choice << endl;
                break;
            case SDLK_x:
                // key cancel
                cout << "cancel" << endl;
                Mix_PlayChannel(-1, _cancel, 0);
                _choice = ENTRY_NUM - 1;
                break;

            case SDLK_z:
                // key select
                Mix_PlayChannel(-1, _ok, 0);
                _exit = true;
                break;
            default:
                break;
            }
        }
    }

}

void MainMenu::start()
{
    

    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(_bgm, -1);
    }
    gTimer->start();
    cout << "--------Main Menu Start-------" << endl;
    while (!gKbdState->isExit())
    {

        logic();
        if (gTimer->isFrame())
        {
            SDL_RenderClear(gRenderer);
            draw();
            gTimer->count();
            SDL_RenderPresent(gRenderer);
        }
        //SDL_Delay(10);
        //cout << "main thread running" << endl;
    }
    cout << "--------Main Menu End-------" << endl;
    gTimer->stop();


}

bool MainMenu::initialize()
{
    cout << "-----Initializing Menu-----" << endl;
    cout << "Loading Image..." << endl;
    if (!loadImages())
    {
        cout << "Menu Image not loaded!\nError: " << IMG_GetError() << endl;
        return false;
    }
    cout << "Image Loaded." << endl;


    cout << "Loading Sound..." << endl;
    if (!loadSounds())
    {
        cout << "Menu Sound not loaded!\nError: " << Mix_GetError();
        return false;
    }
    cout << "Sound Loaded." << endl;
    
    for (int i = 0; i < ENTRY_NUM; i++)
    {
        choicePosition[i][0] = { 0, 100 * i, CHOICE_WIDTH, CHOICE_HEIGHT };
        choicePosition[i][1] = { 200, 100 * i, CHOICE_WIDTH, CHOICE_HEIGHT };
    }
    cout << "-----Menu Initialized------" << endl;
    printf("\n\n");
    return true;
}



void MainMenu::finalize()
{
    // finalize pictures
    delete _background;
    _background = NULL;
    delete _title;
    _title = NULL;
    delete _menuChoice;
    _menuChoice = NULL;

    // finalize musics
    Mix_HaltMusic();
    Mix_FreeMusic(_bgm);
    _bgm = NULL;
    Mix_FreeChunk(_cancel);
    _cancel = NULL;
    Mix_FreeChunk(_ok);
    _ok = NULL;
    
}

bool MainMenu::loadImages()
{
    _background = new Texture("img/menu_bg2.jpg");
    _menuChoice = new Texture("img/mainmenu_choice.png");
    _title = new Texture("img/mainmenu_title.png");

    if (_background == NULL ||
        _menuChoice == NULL ||
        _title      == NULL)
    {
        cout << "menu_bg load failed!\nError: " << IMG_GetError() << endl;
        return false;
    }

    return true;
}

bool MainMenu::loadSounds(){
    _bgm = Mix_LoadMUS("bgm/mainmenu.mp3");
    _cancel = Mix_LoadWAV("se/se_cancel00.wav");
    _ok = Mix_LoadWAV("se/se_ok00.wav");
    if (_bgm == NULL ||
        _cancel == NULL ||
        _ok == NULL)
    {
        return false;
    }
    return true;

}

void MainMenu::draw()
{
    SDL_Rect choiceOffset = {
        150, // x
        300, // y
        CHOICE_WIDTH, // width
        CHOICE_HEIGHT  // height
    };
    SDL_Rect titleOffset = {
        100,
        100,
        300,
        200
    };
    

    SDL_Rect backgroundOffset = {
        (SCREEN_WIDTH - 1200) / 2,
        (SCREEN_HEIGHT - 677) / 2,
        1200,
        677
    };


    _background->render(NULL, &backgroundOffset);
    _title->render(NULL, &titleOffset);
    // show choice;
    for (int i = 0; i < ENTRY_NUM; i++)
    {
        // if _choice == i, use the second one which represents the selected situation
        _menuChoice->render(&choicePosition[i][_choice == i], &choiceOffset);
        choiceOffset.y += 50;
    }

}

void MainMenu::exit()
{
    cout << "exit game" << endl;
    MainMenu::_exit = true;
}

Stage* MainMenu::next(){

    switch (_choice)
    {
    case 0:
//        return (Stage*) new TutorialStage();
        return nullptr;
        break;
    default:
        return nullptr;
        break;
    }
}