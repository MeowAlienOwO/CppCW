#include "Player.h"

using namespace std;
Player::Player(SDL_Rect panel) : GameObject(panel.x + panel.w /2,
        panel.y + panel.h - 24, 4)
{
    cout << "-------Init Player-------" << endl;

    //_texture = loadTexture("img/player00.png");
    _texture = new Texture("img/player00.png");
    //_mark = 0;
    _flip = SDL_FLIP_NONE;
    _moveState = 0;
    _direction = HERE;
    // normal pic
    for (int i = 0; i < 4; i++)
    {
        _heroine[i] = { 32 * i, 0, 32, 48 };
    }
    // moving pic
    for (int i = 0; i < 7; i++)
    {
        _heroine[i + 4] = { 32 * i, 48, 32, 48 };
    }
    // moving pic
    _panelArea = panel;
    setX(_panelArea.x + _panelArea.w / 2);
    setY(_panelArea.y + _panelArea.h / 2);
    _slow = false;
    _lock = SDL_CreateMutex();

    cout << "-------End Init Player-------" << endl;
}   


Player::~Player()
{

    cout << "-------Destroy Player-------" << endl;
    delete _texture;
    cout << "-------End Destroy Player-------" << endl;
}

void Player::move()
{

    //cout << "move " << _direction << " (" << getX() << "," << getY() << ")" << endl;
    if (_slow)
    {
        setSpeed(2);
    }
    else{
        setSpeed(4);
    }
    switch (_direction)
    {

    case LEFT:
        Player::setX(getX() - getSpeed() * 1);
        if (gTimer->frameNo() % 7 == 0)
        {
            _flip = SDL_FLIP_NONE;

            _moveState++;
            _moveState = MAX(_moveState, 4);
            _moveState = MIN(_moveState, 10);
        }
        //GameObject::setX(getX() - getSpeed() * 1);

        break;
    case RIGHT:
        Player::setX(getX() + getSpeed() * 1);
        //GameObject::setX(getX() + getSpeed() * 1);
        if (gTimer->frameNo() % 7 == 0)
        {
            _flip = SDL_FLIP_HORIZONTAL;

            _moveState++;
            _moveState = MAX(_moveState, 4);
            _moveState = MIN(_moveState, 10);
        }
        break;
    case UP:
        Player::setY(getY() - getSpeed() * 1);
        //GameObject::setY(getY() - getSpeed() * 1);
        if (gTimer->frameNo() % 7 == 0)
        {

            _flip = SDL_FLIP_NONE;
            _moveState = (_moveState + 1) % 4;
        }
        break;
    case DOWN:
        Player::setY(getY() + getSpeed() * 1);
        //GameObject::setY(getY() + getSpeed() * 1);
        if (gTimer->frameNo() % 7 == 0)
        {

            _flip = SDL_FLIP_NONE;
            _moveState = _moveState++ % 4;
        }
        break;
    default:
        if (gTimer->frameNo() % 7 == 0)
        {
            _flip = SDL_FLIP_NONE;
            _moveState = _moveState++ % 4;
            //cout << "change state!" << gTimer->frameNo()<<endl;
        }
        break;
    }

}

void Player::setDirection(Direction direction)
{
       _direction = direction;

}
void Player::attack()
{
    
}

void Player::spell()
{
    
}

void Player::draw()
{
    SDL_Rect position = { getX(), getY(), _heroine[0].w, _heroine[0].h };
    SDL_Point center = { getX() + _heroine[0].w / 2, getY() + _heroine[0].h / 2 };
    _texture->renderEx(&_heroine[_moveState], &position, 0, &center, _flip);
}


std::string Player::getType()
{
    return "Player";
}

void Player::setX(int x)
{
    if (SDL_LockMutex(_lock) == 0){
        if (x < _panelArea.x)
        {
            GameObject::setX(_panelArea.x);
        }
        else if (x + _heroine[0].w > _panelArea.x + _panelArea.w)
        {
            GameObject::setX(_panelArea.x + _panelArea.w - _heroine[0].w);
        }
        else
        {
            GameObject::setX(x);
        }
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }


}
void Player::setY(int y)
{
    if (SDL_LockMutex(_lock) == 0){
        if (y < _panelArea.y)
        {
            GameObject::setY(_panelArea.y);
        }
        else if (y + _heroine[0].h > _panelArea.y + _panelArea.h)
        {
            GameObject::setY(_panelArea.y + _panelArea.h - _heroine[0].h);
        }
        else
        {
            GameObject::setY(y);
        }

        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }


}

int Player::getX()
{
    int x;
    if (SDL_LockMutex(_lock) == 0){ 
        x = GameObject::getX();

        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }

    return x;
}


int Player::getY()
{
    int y;
    if (SDL_LockMutex(_lock) == 0){ 
        y = GameObject::getY();

        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }
    return y;
}

void Player::setFocusMod(bool slow){
    _slow = slow;
}
