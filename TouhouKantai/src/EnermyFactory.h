#ifndef ENERMY_FACTORY_H
#define ENERMY_FACTORY_H

#include "Global.h"
#include "Macro.h"
#include "Player.h"
#include "Enermy.h"

enum EnermyType{
    LILYWHITE, CHIRNO
};
class EnermyFactory{
public:
    Enermy* createEnermy(EnermyType type);

    EnermyFactory(Texture* texture, SDL_Rect panel, Player* player, std::vector<Bullet*>* bullets);
private:
    Texture* _texture;
    SDL_Rect _panel;
    std::vector<Bullet*>* _bullets;
};




#endif