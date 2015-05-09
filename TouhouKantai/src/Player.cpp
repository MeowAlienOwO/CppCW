#include "Player.h"

using namespace std;
Player::Player(SDL_Rect panel) : GameObject({panel.x + panel.w / 2,
                                                panel.y + panel.h - 96,
                                                32, 48}, 4, panel)
{
    cout << "-------Init Player-------" << endl;

    _texture = new Texture("img/player00.png");
    _flip = SDL_FLIP_NONE;
    _moveState = 0;
    _direction = HERE;
    _hp = 3;
    // normal pic
    for (int i = 0; i < 4; i++)
    {
        _heroine[i] = { getW() * i, 0, getW(), getH() };
    }
    // moving pic
    for (int i = 0; i < 7; i++)
    {
        _heroine[i + 4] = { getW() * i, getH() * 1, getW(), getH() };
    }

    _slow = false;

    cout << "-------End Init Player-------" << endl;
}   


Player::~Player()
{

    cout << "-------Destroy Player-------" << endl;
    for (int i = 0; i < _bullets.size(); i++)
    {
        delete _bullets[i];
        _bullets[i] = NULL;
    }

    delete _texture;
    _texture = NULL;
    cout << "-------End Destroy Player-------" << endl;
}

void Player::move()
{

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

        break;
    case RIGHT:
        Player::setX(getX() + getSpeed() * 1);
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
        if (gTimer->frameNo() % 7 == 0)
        {

            _flip = SDL_FLIP_NONE;
            _moveState = (_moveState + 1) % 4;
        }
        break;
    case DOWN:
        Player::setY(getY() + getSpeed() * 1);
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
    //cout << "attack!" << endl;
    Bullet* bullet = new Bullet(_texture, { 128, 0, 16, 16 }, this, NULL, getPanel(),getCenter(), (M_PI * 3) / 2);
    _bullets.push_back(bullet);
//    cout << "start at: (" << getCenter().x << "," << getCenter().y << ")" << endl;
//    cout << "player rect: (" << getX() << "," << getY() << "," << getW() << "," << getH() << ")" << endl;
}

void Player::spell()
{
    cout << "spell!" << endl;
}

void Player::draw()
{
    SDL_Rect position = { getX(), getY(), getW(), getH() };
    SDL_Point center = getCenter();
    _texture->renderEx(&_heroine[_moveState], &position, 0, &center, _flip);


}


std::string Player::getType()
{
    return "Player";
}
int Player::getHP()
{
    return _hp;
}

void Player::setFocusMod(bool slow){
    _slow = slow;
}

bool Player::hit()
{
    return --_hp <= 0;
}
//std::vector<Bullet*>* Player::getBullets()
//{
//    return &_bullets;
//}