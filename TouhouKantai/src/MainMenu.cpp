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
    MainMenu::finalize();
}

void MainMenu::logic()
{
    SDL_Event e;
    while (!menu_exit)
    {
        // deal with key presses
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                menu_exit = true;
            }
            else if (e.type == SDL_KEYDOWN){

                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    // key up
                    choice = ++choice % ENTRY_NUM;
                    Mix_PlayChannel(-1, _ok, 0);
                    cout << choice << endl;

                    break;
                case SDLK_DOWN:
                    // key down
                    choice = --choice < 0 ? choice = ENTRY_NUM - 1 : choice;

                    Mix_PlayChannel(-1, _ok, 0);
                    cout << choice << endl;
                    break;
                case SDLK_x:
                    // key cancel
                    cout << "cancel" << endl;
                    Mix_PlayChannel(-1, _cancel, 0);
                    choice = ENTRY_NUM - 1;
                    break;

                case SDLK_z:
                    // key select
                    Mix_PlayChannel(-1, _ok, 0);
                    menu_exit = true;
                    break;
                default:
                    break;
                }
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

    logic();

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
    //SDL_Delay(500);
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
    // _background
  /*  _background = loadTexture("img/menu_bg2.jpg");
    menuChoice = loadTexture("img/mainmenu_choice.png");
    title = loadTexture("img/mainmenu_title.png");
   */ 
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

    //SDL_RenderClear(gRenderer);
    // show _background
    //render(_background, NULL, &backgroundOffset);
    //render(title, NULL, &titleOffset);
    _background->render(NULL, &backgroundOffset);
    _title->render(NULL, &titleOffset);
    // show choice;
    for (int i = 0; i < ENTRY_NUM; i++)
    {
        // if choice == i, use the second one which represents the selected situation
        //render(menuChoice, &choicePosition[i][choice == i] , &choiceOffset);
        _menuChoice->render(&choicePosition[i][choice == i], &choiceOffset);
        choiceOffset.y += 50;
    }

    //SDL_RenderPresent(gRenderer);
}

void MainMenu::exit()
{
    cout << "exit game" << endl;
    MainMenu::menu_exit = true;
}

Stage* MainMenu::next(){

    switch (choice)
    {
    case 0:
        return (Stage*) new TutorialStage();
        break;
    default:
        return nullptr;
        break;
    }
}