#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Global.h"
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

    Texture* _background;
    Texture* _panel;
    
    SDL_Rect panelArea;
    
    Player* player;

    bool tutorialExit;
};
#endif