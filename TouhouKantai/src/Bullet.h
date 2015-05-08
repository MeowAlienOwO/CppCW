#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject{

public:
    Bullet(Texture* texture, SDL_Rect* src, GameObject* from, GameObject* target, SDL_Rect panel);
    ~Bullet();
    void move();
    void draw();
    
    std::string getType();
private:
    Texture* _texture;
    SDL_Rect* _src;
    GameObject* _target;
    GameObject* _from;
    SDL_Rect* _panel;
    
};

#endif