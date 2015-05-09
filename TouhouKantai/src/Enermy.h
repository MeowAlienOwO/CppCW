#ifndef ENERMY_H
#define ENERMY_H

#include "GameObject.h"
#include "Bullet.h"

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
    void moveTo(int dx, int dy);
    void setState(int state);

    Enermy(Texture* texture, SDL_Rect src,
            SDL_Point start, SDL_Rect panel,
         void (*logic)(Enermy* e, int state) = NULL);
    ~Enermy();

    std::vector<Bullet*> _bullets;
private:
    Texture* _texture;
    SDL_Rect _src;
    Uint8 _state;
    void(*_logic)(Enermy* e, int state);

};

void defaultLogic(Enermy* e, int state);
#endif
