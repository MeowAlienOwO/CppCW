#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Global.h"
#include "Stage.h"
#include "Player.h"
#include "Enermy.h"

class TutorialStage: public Stage{

public:
    bool initialize();
    void draw();
    void finalize();
    void logic();
    void start();
    void exit();
    int getMark();
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
    Texture* _enermy;
    
    SDL_Rect _panelArea;
    
    Player* _player;
    int _mark;
    bool _tutorialExit;
    std::vector<Enermy*> _enermies;
    bool* _judge;
};
#endif