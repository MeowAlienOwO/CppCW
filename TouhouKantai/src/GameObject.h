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
    virtual int getX();
    virtual void setX(int x);
    virtual int getY();
    virtual void setY(int y);
    double getSpeed();
    virtual std::string getType() = 0;
    void setSpeed(double speed);
    virtual void move() = 0;
    virtual void draw() = 0;
    GameObject(int x, int y, double speed);
    virtual ~GameObject();
private:
    SDL_Point _position;
    double _speed;
};

#endif