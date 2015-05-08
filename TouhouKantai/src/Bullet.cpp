#include "Bullet.h"

using namespace std;
Bullet::Bullet(Texture* texture, SDL_Rect src, GameObject* from, GameObject* target, SDL_Rect panel, SDL_Point start, double angle)
    : GameObject({start.x, start.y, src.w, src.h}, from->getSpeed(), panel){
    cout << "creating bullet" << endl;
    _texture = texture;
    _src = src;
    _from = from;
    _target = target;
    _angle = angle;
    SDL_Point p = _from->getCenter();
    setX(p.x);
    setY(p.y);
}


Bullet::~Bullet()
{
    //cout << "destroy bullet" << endl;
}


void Bullet::move()
{
        int dx = getSpeed() * 1 * cos(_angle);
        int dy = getSpeed() * 1 * sin(_angle);
        setX(getX() + dx);
        setY(getY() + dy);

}


void Bullet::draw()
{

    _texture->renderEx(&_src, &getRect(), _angle, &getCenter(), SDL_FLIP_NONE);

}

std::string Bullet::getType()
{
    return "Bullet";
}

void Bullet::setAngle(double angle)
{
    _angle = angle;
    while (_angle < 0)
    {
        _angle += 2 * PI;
    }
    while (_angle > 2 * PI)
    {
        _angle -= 2 * PI;
    }

}


