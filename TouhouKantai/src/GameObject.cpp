#include "GameObject.h"
using namespace std;
/* public field */

GameObject::GameObject(SDL_Rect obj, double speed, SDL_Rect panel)
{
    cout << "-----Init GameObject-----" << endl;
    _obj = obj;
    _panel = panel;
    _lock = SDL_CreateMutex();
    
    _speed = speed;
    cout << "-----Init GameObject finished-----" << endl;
}


GameObject::~GameObject()
{
    cout << "-----Destroying GameObject-----" << endl;
  /*  if (_lock != NULL)
    {*/
        SDL_DestroyMutex(_lock);
        _lock = NULL;
    //}
    cout << "-----Destroy GameObject Finished----" << endl;
}

SDL_mutex* GameObject::getLock()
{
    return _lock;
}

void GameObject::setX(int x)
{
    if (SDL_LockMutex(_lock) == 0){
        if (x < _panel.x)
        {
            _obj.x = _panel.x;
        }
        else if (x + _obj.w > _panel.x + _panel.w)
        {
            _obj.x = (_panel.x + _panel.w - _obj.w);
        }
        else
        {
            _obj.x = x;
        }
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }

}

int GameObject::getX()
{
    int x;
    if (SDL_LockMutex(_lock) == 0){ 
        x = _obj.x;
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }

    return x;
}

void GameObject::setY(int y)
{
    if (SDL_LockMutex(_lock) == 0){
        if (y < _panel.y)
        {
            _obj.y = _panel.y;
        }
        else if (y + _obj.h > _panel.y + _panel.h)
        {
            //GameObject::setX(_panelArea.x + _panelArea.w - _heroine[0].w);
            _obj.y = (_panel.y + _panel.h - _obj.h);
        }
        else
        {
            _obj.y = y;
        }
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }


}

int GameObject::getY()
{
    int y;
    if (SDL_LockMutex(_lock) == 0){ 
        y = _obj.y;
        SDL_UnlockMutex(_lock);
    }
    else{
        cout << "Can't get lock! Error: " << SDL_GetError() << endl;
    }
    return y;
}

int GameObject::getW()
{
    return _obj.w;
}
int GameObject::getH()
{
    return _obj.h;
}

SDL_Point GameObject::getCenter()
{
    return{ _obj.x + _obj.w / 2, _obj.y + _obj.h / 2 };
}

SDL_Rect GameObject::getRect()
{
    return _obj;
}

SDL_Rect GameObject::getPanel()
{
    return _panel;
}
void GameObject::setSpeed(double speed)
{
    _speed = speed;
}

double GameObject::getSpeed()
{
    return _speed;
}

bool GameObject::isAtEdge()
{

    return (_obj.x == _panel.x                    ||
            _obj.y == _panel.y                    ||
            _obj.x + _obj.w == _panel.x + _panel.w||
            _obj.y + _obj.h == _panel.y + _panel.h
        );
}


bool GameObject::collide(GameObject* o)
{
    return !(_obj.x + _obj.w < o->getX()    ||
             _obj.y + _obj.h < o->getY()    ||
             _obj.x > o->getX() + o->getW() ||
             _obj.y > o->getY() + o->getH());
}