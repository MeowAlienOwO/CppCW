#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Bullet.h"
/* Player
 * Player.h/cpp represent the player class.
 *  
 */
typedef enum{
   UP, DOWN, LEFT, RIGHT, HERE
} Direction;

class Player : public GameObject{
public:
    void move();
    void setDirection(Direction dir);
    void attack();
    void spell();
    void draw();
    void setFocusMod(bool slow);
    std::vector<Bullet*>* getBullets();
    std::string getType();

    Player(SDL_Rect panel = {128, 32, 448, 256});
    ~Player();

    std::vector <Bullet*> _bullets;
private: 
    //int _mark;
    Uint8 _moveState;
    SDL_RendererFlip _flip;
    SDL_mutex* _lock;
    Texture* _texture;
    Direction _direction;
    SDL_Rect _heroine[11];
    bool _slow;
};
#endif