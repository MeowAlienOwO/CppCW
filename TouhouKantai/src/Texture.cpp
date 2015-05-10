#include "Texture.h"
using namespace std;

Texture::Texture(std::string path)
{
    _texture = loadTexture(path);
}

Texture::Texture(std::string ttf, std::string str, SDL_Color color, int size)
{

    //cout << "loading text texture!" << endl;
    ///cout << "loading font" << endl;
    TTF_Font* font = TTF_OpenFont(ttf.c_str(), size);
    if (font == NULL)
    {
        cout << "font not loaded\nError: " << TTF_GetError() << endl;
        throw new exception("font not loaded");
    }
    //cout << "loading font finished" << endl;
    //cout << "createing surface" << endl;
    SDL_Surface* surface = TTF_RenderText_Solid(font, str.c_str(), color);
    //cout << "surface closed" << endl;
    if (surface == NULL)
    {
        cout << "can't create surface!Error: " << SDL_GetError() << endl;
    }
    w = surface->w;
    h = surface->h;
    //cout << "changing to texture!" << endl;
    _texture = SDL_CreateTextureFromSurface(Texture::_renderer, surface);

    //cout << "texture changing finished!" << endl;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Texture::~Texture()
{
    //cout << "destroy texture" << endl;
    SDL_DestroyTexture(_texture);

    //cout << "texture destroyed" << endl;
}


void Texture::render(SDL_Rect* src, SDL_Rect* dest)
{
    //if (SDL_LockMutex(Texture::_lock) == 0)
    //{
        SDL_RenderCopy(_renderer, _texture, src, dest);
        //SDL_UnlockMutex(Texture::_lock);
    /*}
    else{
        cout << "Unable to lock! Error:" << SDL_GetError() << endl;
    }*/
}

void Texture::renderEx(SDL_Rect* src, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //if (SDL_LockMutex(Texture::_lock) == 0)
    //{

        SDL_RenderCopyEx(_renderer, _texture, src, dest, angle, center, flip);
    //    SDL_UnlockMutex(Texture::_lock);
    //}
    //else{
    //    cout << "Unable to lock! Error:" << SDL_GetError() << endl;
    //}
}

int Texture::getWidth()
{
    return w;
}

int Texture::getHeight()
{
    return h;
}

void Texture::setRenderer(SDL_Renderer* renderer)
{
    Texture::_renderer = renderer;
}

void Texture::setLock(SDL_mutex* lock)
{
    Texture::_lock = lock;
}

SDL_mutex* Texture::getLock()
{
    return Texture::_lock;
}


SDL_Surface* Texture::loadSurface(std::string path)
{
    SDL_Surface* loaded = NULL;

    //cout << "image loading..." << endl;
    loaded = IMG_Load(path.c_str());
    //cout << "image loading finished" << endl;

    if (loaded == NULL)
    {
        cout << "Image Not Loaded!" << endl;
        return NULL;
    }
    w = loaded->w;
    h = loaded->h;
    return loaded;
}

SDL_Texture* Texture::loadTexture(std::string path)
{
    SDL_Surface* surface = loadSurface(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Texture::_renderer, surface);
    if (texture == NULL)
    {
        cout << "Texture Not Loaded!" << IMG_GetError() << endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

