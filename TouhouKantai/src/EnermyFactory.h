#ifndef ENERMY_FACTORY_H
#define ENERMY_FACTORY_H

#include "Global.h"
#include "Macro.h"

#include "Enermy.h"

typedef enum{
    LILYWHITE, CHIRNO
} EnermyType;
class EnermyFactory{
public:
    Enermy* createEnermy(EnermyType type);

    EnermyFactory(Texture* texture, SDL_Rect panel);
private:
    Texture* _texture;
    SDL_Rect _panel;
};


#endif