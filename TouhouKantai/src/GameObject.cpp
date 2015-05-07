#include "GameObject.h"
using namespace std;
/* public field */

GameObject::GameObject(int x, int y, double speed)
{
    cout << "-----Init GameObject-----" << endl;
    _position.x = x;
    _position.y = y;

    _speed = speed;
    cout << "-----Init GameObject finished-----" << endl;
}


GameObject::~GameObject()
{
    cout << "-----Destroying GameObject-----" << endl;

    cout << "-----Destroy GameObject Finished----" << endl;
}


void GameObject::setX(int x)
{
    _position.x = x;
}

int GameObject::getX()
{
    return _position.x;
}

void GameObject::setY(int y)
{
    _position.y = y;
}

int GameObject::getY()
{
    return _position.y;
}

void GameObject::setSpeed(double speed)
{
    _speed = speed;
}

double GameObject::getSpeed()
{
    return _speed;
}
