#ifndef PLAYER_H
#define PLAYER_H
#include "Main.h"
#include "GameObject.h"
/* Player
 * Player.h/cpp represent the player class.
 *  
 */
typedef enum{
   UP, DOWN, LEFT, RIGHT, HERE
} Direction;

class Player : public GameObject{
public:
    int getMark();
    void setMark(int mark);
    void move();
    void setDirection(Direction dir);
    void attack();
    void spell();
    void draw();
    void setX(int x);
    void setY(int y);
    std::string getType();

    Player(SDL_Rect panel = {128, 32, 448, 256});
    ~Player();

private: 
    int _mark;
    //Uint8 _moveState;
    SDL_mutex* _lock;
    //SDL_Texture* _texture;
    Texture* _texture;
    //SDL_Rect _heroine[];
    SDL_Rect _panelArea;
    SDL_Rect _heroine;
    Direction _direction;
};
#endif