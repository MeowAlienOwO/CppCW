#ifndef ENERMY_H
#define ENERMY_H

#include "GameObject.h"
#include "Bullet.h"
#include "BulletFactory.h"
/*
 * class Enermy
 * represent enermy.
 */

class Enermy : public GameObject{
public:
    void move();
    void draw();
    std::string getType();
    void attack();
    void attack(BulletType type, GameObject* target = NULL,
        SDL_Point* start = NULL, double angle = M_PI / 2,
        double speed = 1);
    void setState(int state);

    Enermy(Texture* texture, SDL_Rect src,
        SDL_Point start, SDL_Rect panel,
        std::vector<Bullet*>* bullets,
         void (*logic)(Enermy* e) = NULL);
    ~Enermy();
    int _state;
private:
    BulletFactory* _bulletFactory;
    Texture* _texture;
    SDL_Rect _src;
    void(*_logic)(Enermy* e);
    std::vector<Bullet*>* _bullets;
};

void defaultLogic(Enermy* e);
#endif
