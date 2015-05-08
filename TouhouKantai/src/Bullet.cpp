#include "Bullet.h"

Bullet::Bullet(Texture* texture, SDL_Rect*src, GameObject* from, GameObject* target, SDL_Rect panel)
    : GameObject({from->getX(), from->getY(), src->w, src->h}, from->getSpeed(), panel){
    _texture = texture;
    _src = src;
    _from = from;
    _target = target;

}


Bullet::~Bullet()
{

}


void Bullet::move()
{

}

void Bullet::draw()
{

}

std::string Bullet::getType()
{
    return "Bullet";
}