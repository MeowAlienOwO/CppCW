#include "BulletFactory.h"
using namespace std;

void randomBullet(Bullet* bullet);

void waterfallBullet(Bullet* bullet);

void targetLockBullet(Bullet* bullet);

BulletFactory::BulletFactory(Texture* texture, SDL_Rect panel, GameObject* from)
{
    _texture = texture;
    _panel = panel;
    _from = from;
}

Bullet* BulletFactory::createBullet(
    BulletType type,  
    GameObject* target, 
    SDL_Point start,
    double angle, 
    double speed)
{

    Bullet* bullet = NULL;
    switch (type)
    {
    case RANDOM:
        bullet = new Bullet(_texture,
        { 128, 96, 32, 32 },
        _from, 
        target,
        _panel, start, angle, 
        randomBullet);
        break;
    case WATERFALL:
        bullet = new Bullet(_texture,
        {96, 96, 32, 32},
        _from, target,
        _panel, start, angle,
        waterfallBullet);
        break;
    case TARGET_LOCK:
        bullet = new Bullet(_texture,
            {64, 96, 32, 32},
            _from, target,
            _panel, start, angle,
            targetLockBullet);
        break;
    default:
        break;
    }
    if (bullet != NULL)
    {
        bullet->setSpeed(speed);
    }

    return bullet;
}


void randomBullet(Bullet* bullet)
{
    cout << "in random bullet, bullet == NULL?" << (bullet == NULL) << endl;
    srand((unsigned int)(time(NULL)));
    int dir = rand() % 4;
    switch (dir)
    {
    case 0:
        bullet->setX(bullet->getX() + bullet->getSpeed());
        break;
    case 1:
        bullet->setX(bullet->getX() - bullet->getSpeed());
        break;
    case 2:
        bullet->setY(bullet->getY() + bullet->getSpeed());
        break;
    case 3:
        bullet->setY(bullet->getY() - bullet->getSpeed());
        break;
    }
}


void waterfallBullet(Bullet* bullet)
{
    static double x_v = bullet->getSpeed() * sin(bullet->getAngle());
    static double y_v = bullet->getSpeed() * cos(bullet->getAngle());
    double a = 0.1;
    double dx = x_v;
    double dy = y_v;
    cout << "angle = " << bullet->getAngle() * 180 / M_PI << endl;

    //bullet->setX(bullet->getX() + bullet->getSpeed() * sin(bullet->getAngle()));
    //bullet->setY(bullet->getY() + bullet->getSpeed() * cos(bullet->getAngle()));
    bullet->setX(bullet->getX() + x_v);
    bullet->setY(bullet->getY() + y_v);
    y_v += a;
//    bullet->setAccelerate(0, 0.3);
}

void targetLockBullet(Bullet* bullet)
{
    double dx = bullet->getTarget()->getCenter().x - bullet->getCenter().x;
    double dy = bullet->getTarget()->getCenter().y - bullet->getCenter().y;
    double angle = atan(dy / dx);
    cout << "angle = " << angle << endl;
    bullet->setAngle(angle);

    bullet->setX(bullet->getX() + bullet->getSpeed() * cos(angle));
    bullet->setY(bullet->getY() + bullet->getSpeed() * sin(angle));

}


