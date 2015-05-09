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

    _tutorialExit = false;
    cout << "-----End Stage Tutorial-----" << endl;
}

TutorialStage::~TutorialStage()
{
    TutorialStage::finalize();
        
}

bool TutorialStage::initialize()
{
    
    _panelArea = { 128, 32, 448, 672 };
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
    _player->draw();

    for (int i = 0; i < _player->_bullets.size(); i++)
    {
        _player->_bullets[i]->draw();
    }
    drawBackground();
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
    if (gTimer->isFrame())
    {
        _player->move();

        for (int i = 0; i < _player->_bullets.size(); i++)
        {
            _player->_bullets[i]->move();
            if (_player->_bullets[i]->isAtEdge())
            {
                delete _player->_bullets[i];
                _player->_bullets.erase(_player->_bullets.begin() + i);
            }
        }
        // reduce the extra space
        std::vector<Bullet*>(_player->_bullets).swap(_player->_bullets);

        // remove the print part the program won't work;
        //cout << "move " << " (" << _player->getX() << "," << _player->getY() << ")" << endl;
    }


}

void TutorialStage::start()
{
    cout << "--------Tutorial Start--------" << endl;
    gTimer->start();
    while (!_tutorialExit)
    {
        // release cpu
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //std::this_thread::sleep_for(std::chrono::microseconds(1));
        //SDL_Delay(1);
        logic();
        if (gTimer->isFrame())
        {
            SDL_RenderClear(gRenderer);
            draw();
            gTimer->renderFPS();
            gTimer->count();
            SDL_RenderPresent(gRenderer);
        }
    }
    gTimer->stop();
    cout << "--------Tutorial End--------" << endl;

}

void TutorialStage::exit()
{
    cout << "exit tutorial stage!" << endl;
    _tutorialExit = true;
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
    _player = new Player(_panelArea);
    if (nullptr == _player)
    {
        return false;
    }

    cout << "-----Object Load Finished-----" << endl;

    return true;
}

void TutorialStage::freeObject()
{
    cout << "-----Start Free Object-----" << endl;
    delete _player;
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
            if ((offset.x >= _panelArea.x &&
                offset.x <= _panelArea.x + _panelArea.w - bgSrc.w)
                &&
                (offset.y >= _panelArea.y &&
                offset.y <= _panelArea.y + _panelArea.h - bgSrc.h))
            {
                // case the _background tile is in panel area
            }
            else
            {
                _background->render(&bgSrc, &offset);
            }

        }

    }
}

void TutorialStage::drawPanel()
{

    static SDL_Rect panelBgDest = {_panelArea.x, _panelArea.y - 960, _panelArea.w, 960};
    static int count = 0;
    SDL_Rect panelBgSrc = { 0, 0, 256, 256 };
    SDL_Rect panelTreeSrcL = { 256, 0, 128, 256 };
    SDL_Rect panelTreeSrcR = { 384, 0, 128, 256 };
    
    if (panelBgDest.y + panelBgDest.h + 1 < (_panelArea.y + _panelArea.h))
    {
        panelBgDest.y = _panelArea.y;

    }
    else if (count = (++count %100) )
    {
        panelBgDest.y -- ;
    }
    
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
            case SDLK_z:
                    _player->attack();
                break;
            case SDLK_x:
                _player->spell();
                break;
            case SDLK_LSHIFT:
                _player->setFocusMod(true);
                break;
            case SDLK_UP:
                _player->setDirection(UP);
                break;
            case SDLK_DOWN:
                _player->setDirection(DOWN);
                break;
            case SDLK_LEFT:
                _player->setDirection(LEFT);
                break;
            case SDLK_RIGHT:
                _player->setDirection(RIGHT);
                break;
            default:
                break;
            }
            
        }
        else if (e.type == SDL_KEYUP)
        {
            SDL_Event next;

            switch (e.key.keysym.sym)
            {
            case SDLK_LSHIFT:
                _player->setFocusMod(false);
            case SDLK_UP:
                _player->setDirection(HERE);
                break;
            case SDLK_DOWN:
                _player->setDirection(HERE);
                break;
            case SDLK_LEFT:
                _player->setDirection(HERE);
                break;
            case SDLK_RIGHT:
                _player->setDirection(HERE);
                break;
            default:
                break;

            }


        }


    }
}