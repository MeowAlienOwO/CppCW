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
   finalize();
}

bool TutorialStage::initialize()
{
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
    _mark = 0;
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

    for (int i = 0; i < _enermies.size(); i++)
    {
        _enermies[i]->draw();
        for (int j = 0; j < _enermies[i]->_bullets.size(); j++)
        {
            _enermies[i]->_bullets[j]->draw();
        }
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
    if (gTimer->isFrame())
    {

        handleKbdEvent();
        _player->move();

        for (int i = 0; i < _player->_bullets.size(); i++)
        {
            Bullet* bullet = _player->_bullets[i];
            bullet->move();
            if (_player->_bullets[i]->isAtEdge())
            {
                delete _player->_bullets[i];
                _player->_bullets.erase(_player->_bullets.begin() + i);
                break;
            }
            else
            {
                for (int j = 0; j < _enermies.size(); j++)
                {
                    Enermy* enermy = _enermies[j];
                    if (bullet->collide(enermy))
                    {
                        cout << "hit enermy!" << endl;
                        delete enermy;
                        _enermies.erase(_enermies.begin() + j);
                        delete bullet;
                        _player->_bullets.erase(_player->_bullets.begin() + i);
                        _mark += 10;
                        break;
                    }
                }
            }
        }

        // reduce the extra space
        std::vector<Bullet*>(_player->_bullets).swap(_player->_bullets);
        std::vector<Enermy*>(_enermies).swap(_enermies);

        for (int i = 0; i < _enermies.size(); i++)
        {
            _enermies[i]->move();

            for (int j = 0; j < _enermies[i]->_bullets.size(); j++)
            {
                Bullet* bullet =  _enermies[i]->_bullets[j];
                bullet->move();
                if (bullet->collide(_player))
                {
                    cout << "hit player!" << endl;
                    if (_player->hit())
                    {
                        exit();
                        cout << "player die!" << endl;
                        break;
                    }
                    delete bullet;

                    _enermies[i]->_bullets.erase(_enermies[i]->_bullets.begin() + j);
                }
                else if (bullet->isAtEdge())
                {
                    delete bullet;
                    _enermies[i]->_bullets.erase(_enermies[i]->_bullets.begin() + j);
                }
                
            }
            std::vector<Bullet*>(_enermies[i]->_bullets).swap(_enermies[i]->_bullets);
        }

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

    drawMark();
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
    _enermy = new Texture("img/stg1enm.png");

    _panelArea = { 112, 16, 480, 704 };
    _playerText = { 0, 112, 64, 16 };
    _bombText = { 0, 128, 64, 16 };
    _playerStar = { 64, 80, 16, 16 };
    _bombStar = { 80, 80, 16, 16 };
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

    Enermy* enermy = new Enermy(_enermy, { 0, 256, 32, 56 },
    { _panelArea.x + _panelArea.w / 2, _panelArea.y + _panelArea.h / 2 },
    _panelArea);
    _enermies.push_back(enermy);

    //_judge = (bool*)malloc(sizeof(bool) * (_panelArea.w * _panelArea.h));
    cout << "-----Object Load Finished-----" << endl;
    return true;
}

void TutorialStage::freeObject()
{
    cout << "-----Start Free Object-----" << endl;
    delete _player;
    for (int i = 0; i < _enermies.size(); i++)
    {
        delete _enermies[i];
        _enermies.erase(_enermies.begin() + i);
    }
    //free(_judge);
    //_judge = NULL;
    cout << "-----Object Free Finished-----" << endl;
   
}

void TutorialStage::drawBackground()
{
    // set background tile source and offset
    SDL_Rect bgSrc = { 0, 224, 32, 32 };
    //SDL_Rect bgSrc = {}
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

    SDL_Rect _playerTextDest = { _panelArea.x + _panelArea.w + 32,
                                    _panelArea.y + _panelArea.h / 3, 
                                    _playerText.w, _playerText.h };
    _background->render(&_playerText, &_playerTextDest);
    SDL_Rect _playerStarDest = { _playerTextDest.x + _playerTextDest.w, _playerTextDest.y, 
        _playerStar.w, _playerStar.h};

    for (int i = 0; i < _player->getHP(); i++)
    {
        cout << "drawing hp star" << endl;
        _background->render(&_playerStar, &_playerStarDest);
        _playerStarDest.x += _playerStar.w;
    }
    SDL_Rect _bombTextDest = { _playerTextDest.x, _playerTextDest.y + _playerTextDest.h + 16,
                                _bombText.w, _bombText.h };
    _background->render(&_bombText, &_bombTextDest);

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

void TutorialStage::drawMark()
{
    SDL_RenderClear(gRenderer);

    string markStr;
    ostringstream sstream;
    // change float to string && cut after two decimal numbers
    sstream << _mark;
    markStr = sstream.str();
    Texture* markText = new Texture("font/font.ttf", "Your Mark", { 0x00, 0x00, 0x00, 0xFF }, 64);
    
    SDL_Rect markTextDest = { SCREEN_WIDTH / 2 - markText->getWidth() / 2,
                            SCREEN_HEIGHT / 2 - 300, 
                            markText->getWidth(), 
                            markText->getHeight()
                        };
    //printf("position:(%d,%d,%d,%d)\n", position.x, position.y, position.w, position.h);
//    Texture* markText = new Texture()
    Texture* scoreBg = new Texture("img/score_bg.jpg");
    SDL_Rect screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    scoreBg->render(NULL, &screenRect);
    cout << "render score BG finished" << endl;
    markText->render(NULL, &markTextDest);
    cout << "render score text finished " << endl;
    delete markText;
    markText = new Texture("font/font.ttf", markStr, { 0x00, 0x00, 0x00, 0xFF }, 64);
    
    markTextDest = { SCREEN_WIDTH / 2 - markText->getWidth() / 2,
                            SCREEN_HEIGHT / 2 - 300 + markText->getHeight(), 
                            markText->getWidth(), 
                            markText->getHeight()
                        };

    markText->render(NULL, &markTextDest);
    SDL_RenderPresent(gRenderer);
    SDL_Event e;
    bool quit = false;
    while (!quit){

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_q)
                {
                    quit = true;
                }
            }
        }
    }

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