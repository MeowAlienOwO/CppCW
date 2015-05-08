#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Global.h"
/* GameObject
 * GameObject.h/cpp define and implement the father class of all game object,
 * like player, enermy, bullet, boss, etc.
 * 
 * Every GameObject must have these properties: 
 * - Has position
 * - Know how to move
 * - Know how to draw 
 *
 * GameObject Inheritance Relation:
 * GameObject
 *     |----Player
 *     |----Bullet
 *     |----Enermy
 *            |----Boss
 * 
 */
class GameObject{

public:
    // move-related methods
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getW();
    int getH();
    SDL_Rect getRect();
    SDL_Point getCenter();
    SDL_Rect getPanel();
    bool isAtEdge();
    void setSpeed(double speed);
    double getSpeed();
    virtual ~GameObject();
    virtual void move() = 0;
    virtual void draw() = 0;
    virtual std::string getType() = 0;
    GameObject(SDL_Rect obj, double speed, SDL_Rect panel);
    SDL_mutex* getLock();
private:
    SDL_Rect _obj;
    SDL_Rect _panel;
    double _speed;
    SDL_mutex* _lock;
};

#endif