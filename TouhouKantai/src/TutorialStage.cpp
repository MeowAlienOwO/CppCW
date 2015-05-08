#include "TutorialStage.h"

using namespace std;
/* public field */
TutorialStage::TutorialStage()
{
    cout << "-----Stage: Tutorial-----" << endl;
    if (!initialize())
    {
        cout << "Tutorial Not Created!" << endl;
        finalize();
        throw exception("Initialize failed");
    }

    tutorialExit = false;
    cout << "-----End Stage Tutorial-----" << endl;
}
TutorialStage::~TutorialStage()
{
    TutorialStage::finalize();
        
}

bool TutorialStage::initialize()
{
    
    panelArea = { 128, 32, 448, 672 };
    if (!loadImage())
    {
        cout << "Image Load Failed!\nError: " << IMG_GetError() << endl;
    }

    if (!loadMusic())
    {
        cout << "Music Load Failed!\nError: " << Mix_GetError() << endl;
    }

    if (!loadObject())
    {
        cout << "Object Load Failed!\nError: " << SDL_GetError() << endl;
    }

    cout << "-----End Tutorial Init-----" << endl;
    

    return true;
}

void TutorialStage::draw()
{
    // draw background
    //SDL_RenderClear(gRenderer);
    //drawPanel();

    player->draw();
    drawBackground();
    //gTimer->renderFPS();
}

void TutorialStage::finalize()
{
    cout << "-----Start Finalize Tutorial-----" << endl;
    freeObject();
    freeImage();
    freeMusic();
    cout << "-----Tutorial Finalize Finished-----" << endl;
}


void TutorialStage::logic()
{
    handleKbdEvent();
    //int x = player->getX();
    //int y = player->getY();
    //bool isframe = gTimer->isFrame();

    if (gTimer->isFrame())
    {
        //player->draw();
        player->move();
        // remove the print part the program won't work;
        cout << "move " << " (" << player->getX() << "," << player->getY() << ")" << endl;
    }


}

void TutorialStage::start()
{
    cout << "--------Tutorial Start--------" << endl;
    while (!tutorialExit)
    {
        // release cpu
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //SDL_Delay(1);
        logic();
    
   }
    cout << "--------Tutorial End--------" << endl;
    
}

void TutorialStage::exit()
{
    cout << "exit tutorial stage!" << endl;
    tutorialExit = true;
}



Stage* TutorialStage::next()
{
    cout << "goto next stage!" << endl;
    return nullptr;
}

/* private field */
bool TutorialStage::loadImage()
{
    cout << "-----Start Load Image-----" << endl;
//    background = loadTexture("img/tutorial_bg.png");
    //background = loadTexture("img/front.png");
    //panel = loadTexture("img/stg1bg.png");
    _background = new Texture("img/front.png");
    _panel = new Texture("img/tutorial_bg.png");
    cout << "-----Image Load Finished-----" << endl;

    return true;
}

void TutorialStage::freeImage()
{
    cout << "-----Start Free Image-----" << endl;
    delete _background;
    delete _panel;
    cout << "-----Image Free Finished-----" << endl;
}

bool TutorialStage::loadMusic()
{
    cout << "-----Start Load Music-----" << endl;
    
    cout << "-----Music Load Finished-----" << endl;

    return true;
}

void TutorialStage::freeMusic()
{
    cout << "-----Start Free Music-----" << endl;
    
    cout << "-----Music Free Finished-----" << endl;


}
bool TutorialStage::loadObject()
{
    cout << "-----Start Load Object-----" << endl;
    //player = *new Player(panelArea);
    player = new Player(panelArea);
    if (nullptr == player)
    {
        return false;
    }

    cout << "-----Object Load Finished-----" << endl;

    return true;
}

void TutorialStage::freeObject()
{
    cout << "-----Start Free Object-----" << endl;
    delete player;
    cout << "-----Object Free Finished-----" << endl;
   
}

void TutorialStage::drawBackground()
{
    // set background tile source and offset
    SDL_Rect bgSrc = { 0, 224, 32, 32 };
    SDL_Rect offset = { 0, 0, bgSrc.w, bgSrc.h };

    for (offset.x = 0; offset.x < SCREEN_WIDTH; offset.x += offset.w)
    {
        for (offset.y = 0; offset.y < SCREEN_HEIGHT; offset.y += offset.h)
        {
            if ((offset.x >= panelArea.x &&
                offset.x <= panelArea.x + panelArea.w - bgSrc.w)
                &&
                (offset.y >= panelArea.y &&
                offset.y <= panelArea.y + panelArea.h - bgSrc.h))
            {
                // case the _background tile is in panel area
            }
            else
            {
                //render(_background, &bgSrc, &offset);
                _background->render(&bgSrc, &offset);
            }

        }

    }
}

void TutorialStage::drawPanel()
{

    static SDL_Rect panelBgDest = {panelArea.x, panelArea.y - 960, panelArea.w, 960};
    static int count = 0;
    SDL_Rect panelBgSrc = { 0, 0, 256, 256 };
    SDL_Rect panelTreeSrcL = { 256, 0, 128, 256 };
    SDL_Rect panelTreeSrcR = { 384, 0, 128, 256 };
    
    if (panelBgDest.y + panelBgDest.h + 1 < (panelArea.y + panelArea.h))
    {
        panelBgDest.y = panelArea.y;

    }
    else if (count = (++count %100) )
    {
        panelBgDest.y -- ;
    }
    
    //render(panel, &panelBgSrc, &panelArea);
    //render(panel, &panelBgSrc, &panelBgDest);
    _panel->render(&panelBgSrc, &panelBgDest);
  
}

void TutorialStage::handleKbdEvent()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        // TODO: the solution still can't get rid of ups. using pushdown automata?
        if (e.type == SDL_QUIT)
        {
            exit();
        }
        else if (e.type == SDL_KEYDOWN)
        {
            
            switch (e.key.keysym.sym)
            {
            case SDLK_q:
                    exit();
                    break;
            case SDLK_LSHIFT:
                player->setFocusMod(true);
                break;
            case SDLK_UP:
                player->setDirection(UP);
                //SDL_PumpEvents();
                SDL_FlushEvent(SDL_KEYUP);
                break;
            case SDLK_DOWN:
                player->setDirection(DOWN);
                //SDL_PumpEvents();
                SDL_FlushEvent(SDL_KEYUP);
                break;
            case SDLK_LEFT:
                player->setDirection(LEFT);
                //SDL_PumpEvents();
                SDL_FlushEvent(SDL_KEYUP);
                break;
            case SDLK_RIGHT:
                player->setDirection(RIGHT);
                //SDL_PumpEvents();
                SDL_FlushEvent(SDL_KEYUP);
                break;
            default:
                break;
            }
            
        }
        else if (e.type == SDL_KEYUP)
        {
            SDL_Event next;
            //filter the first keyup generated by windows
            if (!SDL_PollEvent(&next) && next.type != SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_LSHIFT:
                    player->setFocusMod(false);
                case SDLK_UP:
                    player->setDirection(HERE);
                    //SDL_FlushEvent(SDL_KEYUP);
                    break;
                case SDLK_DOWN:
                    player->setDirection(HERE);
                    //SDL_FlushEvent(SDL_KEYDOWN);
                    break;
                case SDLK_LEFT:
                    player->setDirection(HERE);
                    //SDL_FlushEvent(SDL_KEYDOWN);
                    break;
                case SDLK_RIGHT:
                    player->setDirection(HERE);
                    //SDL_FlushEvent(SDL_KEYDOWN);
                    break;
                default:
                    break;

                }
            }

        }

//        SDL_FlushEvent(SDL_KEYDOWN);
//        SDL_FlushEvent(SDL_KEYUP);
    }
}