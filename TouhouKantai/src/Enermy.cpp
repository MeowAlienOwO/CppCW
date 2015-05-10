#include "Enermy.h"
using namespace std;

void defaultLogic(Enermy* e);

Enermy::Enermy(Texture* texture, SDL_Rect src, SDL_Point start,
    SDL_Rect panel,
    std::vector<Bullet*>* bullets,
    void (*logic)(Enermy* e))
    : GameObject({ start.x, start.y, src.w, src.h }, 2, panel)
{
    cout << "init enermy" << endl;
    _texture = texture;
    _src = src;
    _state = 0;
    _bullets = bullets;
    _bulletFactory = new BulletFactory(_texture, getPanel(), this);
    cout << "logic = " << logic << endl;
    _logic = logic == NULL? defaultLogic : logic;
}

Enermy::~Enermy()
{
    //for (int i = 0; i < _bullets.size(); i++)
    //{
    //    delete _bullets[i];
    //}
}

void Enermy::move()
{
    _logic(this);
}

void Enermy::draw()
{
    _texture->renderEx(&_src, &getRect(), 0, &getCenter(), SDL_FLIP_NONE);
}

void Enermy::attack()
{
    Bullet* bullet;
    for (int i = 0; i < 8; i++)
    {
        bullet = new Bullet(_texture, { 128, 96, 32, 32 }, this, NULL, getPanel(), getCenter(), (M_PI * i) / 4);
        _bullets->push_back(bullet);
    }
}
void Enermy::attack(BulletType type, GameObject* target, SDL_Point* start, double angle, double speed)
{
    Bullet* bullet;
    if (start == NULL)
    {
        bullet = _bulletFactory->createBullet(type, target, getCenter(), angle, speed);
    }
    else
    {
        bullet = _bulletFactory->createBullet(type, target, *start, angle, speed);
    }

    if (bullet != NULL)
    {
        _bullets->push_back(bullet);
    }
}

//void Enermy::moveTo(int dx, int dy)
//{
//    setX(getX() + dx);
//    setY(getY() + dy);
//}

std::string Enermy::getType()
{
    return "Enermy";
}


void defaultLogic(Enermy* e)
{
    static int count = gTimer->frameNo();
    int c = gTimer->frameNo();
    if (c - count > 240)
    {
        count = c;
        e->attack();
    }
}

