#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject{

public:
    Bullet(Texture* texture, SDL_Rect src, GameObject* from, 
            GameObject* target, SDL_Rect panel,SDL_Point start, 
            double angle = PI / 2, 
            void (*logic)(Bullet* bullet) = NULL);
    ~Bullet();

    virtual void move();
    void defaultMove();
    GameObject* getTarget();
    GameObject* getFrom();
    void draw();
    void setAngle(double angle);
    void setAccelerate(double ax, double ay); 
    double getAngle();
    std::string getType();
    int _state;
private:
    Texture* _texture;
    SDL_Rect _src;
    GameObject* _target;
    GameObject* _from;
    double _angle;
    double _ax;
    double _ay;
    void(*_logic)(Bullet* bullet);
};

#endif