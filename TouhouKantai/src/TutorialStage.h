#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Main.h"
#include "Stage.h"
#include "Player.h"

class TutorialStage: public Stage{

public:
    bool initialize();
    void draw();
    void finalize();
    void logic();
    void start();
    void exit();
    Stage* next();
    TutorialStage();
    ~TutorialStage();

private:

    bool loadImage();
    void freeImage();
    bool loadMusic();
    void freeMusic();
    bool loadObject();
    void freeObject();
    void drawBackground();
    void drawPanel();
    void handleKbdEvent();
    void checkUserMove();
    SDL_Texture* background;

    SDL_Texture* panel;
    
    SDL_Rect panelArea;
    
    Player* player;

    bool tutorialExit;
};
#endif