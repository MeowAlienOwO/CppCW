#include "EnermyFactory.h"
using namespace std;
namespace EnermyScript{
    Player* _player;
    void lilyMove(Enermy* e);
    void chirnoMove(Enermy* e);
}
EnermyFactory::EnermyFactory(Texture* texture, SDL_Rect panel, Player* player, std::vector<Bullet*>* bullets)
{

    _texture = texture;
    cout << "texture == NULL?" << (_texture == NULL) << endl;
    _panel = panel;
    _bullets = bullets;
    EnermyScript::_player = player;
    //cout << "panel == NULL?" << (_panel == NULL) << endl;
}

Enermy* EnermyFactory::createEnermy(EnermyType type)
{
    Enermy* enermy = NULL;
    switch (type)
    {
    case LILYWHITE:
        enermy = new Enermy(_texture, { 0, 0, 32, 32 }, { _panel.x + 16, _panel.y + 16 }, _panel, _bullets, EnermyScript::lilyMove);
        break;
    case CHIRNO:
        enermy = new Enermy(_texture, { 0, 256, 32, 56 }, { _panel.x + _panel.w / 2, _panel.y + _panel.h / 2}, _panel, _bullets, EnermyScript::chirnoMove);
        break;
    default:
        break;
    }

    return enermy;
}

namespace EnermyScript
{

    void lilyMove(Enermy* e)
    {
        e->setX(e->getX() + e->getSpeed());
        if (e->getX() < (e->getPanel().x + e->getPanel().w / 2))
        {
            e->setY(e->getY() + e->getSpeed());

        }
        else
        {

            e->setY(e->getY() - e->getSpeed());
        }
        static int count = gTimer->frameNo();
        int c = gTimer->frameNo();
        if (c - count > 40)
        {
            count = c;
            e->attack();
        }
    }
    void chirnoMove(Enermy* e)
    {

        cout << "chirono moving!" << endl;
        static int count = gTimer->frameNo();
        static int state = 0;
        static SDL_Point center = { e->getPanel().x + e->getPanel().w / 2,
            e->getPanel().y + e->getPanel().h / 2 };
        double dx = center.x - e->getX();
        double dy = center.y - e->getY();
        double angle = atan(dy / dx);
        //e->setX(e->getX() + e->getSpeed() * cos(angle));
        //e->setY(e->getY() + e->getSpeed() * sin(angle));
        int c = gTimer->frameNo();
        if (c - count > 60)
        {
            count = c;
            cout << "chirono attacking! code:"<< state << endl;
            cout << "_player == NULL? " << (_player == NULL) << endl;
            //e->attack();
            switch (state)
            {
            case 0:
                e->attack(RANDOM, NULL);
                break;
            case 1:
                e->attack(WATERFALL, NULL, &e->getCenter(), M_PI  / 6, 2.0);
                break;
            case 2:
                //e->attack(TARGET_LOCK, _player);
                break;
            default:
                break;
            }

            state = ++state % 3;
        }
    }
}
