#ifndef MAINMENU_H
#define MAINMENU_H
//#include "Main.h"
#include "Global.h"
#include "TutorialStage.h"
#include "Stage.h"

 
#define ENTRY_NUM  2
#define CHOICE_WIDTH 200
#define CHOICE_HEIGHT 100

/*
 * MainMenu 
 * MainMenu mainly contains what is needed in the main menu,
 * including the image/audio stuff and several entrances for different function,
 * like new game, etc.
 */

class MainMenu : public Stage{
public:
    void logic();
    void draw();
    bool initialize();
    void finalize();
    void start();
    void exit();
    Stage* next();
    MainMenu();
    ~MainMenu();
private:
    bool loadImages();
    bool loadSounds();
    void newGame();
    //const static int ENTRY_NUM = 2;
    //const static int CHOICE_WIDTH = 200;
    //const static int CHOICE_HEIGHT = 100;

    bool _exit;
    int _choice;
//    SDL_Texture* _backgrou
//    SDL_Texture* menuChoice;
//    SDL_Texture* title;
    Texture* _background;
    Texture* _menuChoice;
    Texture* _title;
    SDL_Rect choicePosition[ENTRY_NUM][2];

    Mix_Music* _bgm;
    Mix_Chunk* _cancel;
    Mix_Chunk* _ok;

};

#endif

