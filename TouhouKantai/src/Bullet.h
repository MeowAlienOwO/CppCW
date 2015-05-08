#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject{

public:
    Bullet(Texture* texture, SDL_Rect src, GameObject* from, 
            GameObject* target, SDL_Rect panel,SDL_Point start, 
            double angle = 0);
    ~Bullet();
    virtual void move();
    void draw();
    void setAngle(double angle);
    double getAngle();
    std::string getType();
private:
    Texture* _texture;
    SDL_Rect _src;
    GameObject* _target;
    GameObject* _from;
    double _angle;
};

#endif