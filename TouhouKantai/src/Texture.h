#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Texture{

public:
    Texture(std::string path);
    Texture(std::string ttf, std::string str, SDL_Color color, int size);
    ~Texture();
    void render(SDL_Rect* src, SDL_Rect* dest);
    void renderEx(SDL_Rect* src, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip);
    int getWidth();
    int getHeight();
    static void setRenderer(SDL_Renderer* renderer);
    static void setLock(SDL_mutex* lock);
    static SDL_mutex* getLock();
    
private:
    
    SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadTexture(std::string path);

    SDL_Texture* _texture;
    int w, h;
    static SDL_Renderer* _renderer;
    static SDL_mutex* _lock;
};


#endif