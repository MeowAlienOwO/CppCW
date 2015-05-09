#include "Enermy.h"
using namespace std;

Enermy::Enermy(Texture* texture, SDL_Rect src, SDL_Point start, SDL_Rect panel, void (*logic)(Enermy* e, int state))
    : GameObject({ start.x, start.y, src.w, src.h }, 2, panel)
{
    _texture = texture;
    _src = src;
    _state = 0;
    _logic = logic == NULL? defaultLogic : logic;
}

Enermy::~Enermy()
{
    for (int i = 0; i < _bullets.size(); i++)
    {
        delete _bullets[i];
    }
}

void Enermy::move()
{
    _logic(this, _state);
}

void Enermy::draw()
{
    _texture->renderEx(&_src, &getRect(), 0, &getCenter(), SDL_FLIP_NONE);
}

void Enermy::attack()
{
    for (int i = 0; i < 8; i++)
    {
        Bullet* bullet = new Bullet(_texture, { 128, 96, 32, 32 }, this, NULL, getPanel(), getCenter(), (M_PI * i) / 4);
        _bullets.push_back(bullet);

    }
}

void Enermy::moveTo(int dx, int dy)
{
    setX(getX() + dx);
    setY(getY() + dy);
}

std::string Enermy::getType()
{
    return "Enermy";
}


void defaultLogic(Enermy* e, int state)
{
    static int count = gTimer->frameNo();
    int c = gTimer->frameNo();
    if (c - count >240 )
    {
        count = c;
        e->attack();
    }
}

