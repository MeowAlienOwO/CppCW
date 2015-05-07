#include "Player.h"

using namespace std;
Player::Player(SDL_Rect panel) : GameObject(panel.x + panel.w /2,
        panel.y + panel.h - 24, 2)
{
    cout << "-------Init Player-------" << endl;

    //_texture = loadTexture("img/player00.png");
    _texture = new Texture("img/player00.png");
    _mark = 0;
    _direction = HERE;
    _panelArea = panel;
    _heroine = { 0, 0, 32, 64 };
    setX(_panelArea.x + _panelArea.w / 2);
    setY(_panelArea.y + _panelArea.h / 2);
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
    if (SDL_LockMutex(_lock) == 0)
    {
        switch (_direction)
        {

        case LEFT:
            Player::setX(getX() - getSpeed() * 1);
            //GameObject::setX(getX() - getSpeed() * 1);
            break;
        case RIGHT:
            Player::setX(getX() + getSpeed() * 1);
            //GameObject::setX(getX() + getSpeed() * 1);
            break;
        case UP:
            Player::setY(getY() - getSpeed() * 1);
            //GameObject::setY(getY() - getSpeed() * 1);
            break;
        case DOWN:
            Player::setY(getY() + getSpeed() * 1);
            //GameObject::setY(getY() + getSpeed() * 1);
            break;
        default:
            break;
        }

        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }
       //cout << "move " << _direction << " (" << getX() << "," << getY() << ")" << endl;
    //setDirection(HERE);
    
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
    //if (SDL_LockMutex(_lock) == 0)
    //{
        SDL_Rect position = { getX(), getY(), _heroine.w, _heroine.h };
        //render(_texture, &_heroine, &position);
        _texture->render(&_heroine, &position);
    //    SDL_UnlockMutex(_lock);
    //}
    //else{
    //    cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    //}
    
    //printf("position:(%d,%d,%d,%d\n)", position.x, position.y, position.w, position.h);
    //SDL_RenderCopy(gRenderer, _texture, &_heroine, &position);
    
}

int Player::getMark()
{
    return _mark;
}


std::string Player::getType()
{
    return "Player";
}

void Player::setX(int x)
{
    if (x < _panelArea.x)
    {
        GameObject::setX(_panelArea.x);
    }
    else if (x + _heroine.w > _panelArea.x + _panelArea.w)
    {
        GameObject::setX(_panelArea.x + _panelArea.w - _heroine.w);
    }
    else
    {
        GameObject::setX(x);
    }

}
void Player::setY(int y)
{
    if (y < _panelArea.y)
    {
        GameObject::setY(_panelArea.y);
    }
    else if (y + _heroine.h > _panelArea.y + _panelArea.h)
    {
        GameObject::setY(_panelArea.y + _panelArea.h - _heroine.h);
    }
    else
    {
        GameObject::setY(y);
    }

}