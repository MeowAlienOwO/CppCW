#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "Timer.h"
#include "Texture.h"
/*
 * Author: Zhang Huayan
 * ID: 6511043
 * Main
 * Main.h/Main.cpp defines the entry of the game and provides several 
 * functions for loading image and drawing.
 * The procedure of drawing is discribed as:
 * 1. load all pictures, do logic and picture position calculation
 * 2. after processing logic and position setting, put all surface on surface 
 * 3. change surface into texture
 * 4. copy texture to window renderer
 * 5. use renderer to show the picture
 * 
 * Main is not going to use any OOP structure since it is clear using Procedure programming.
 */
const static int SCREEN_WIDTH  = 960;
const static int SCREEN_HEIGHT = 720;

extern Timer *gTimer;
extern SDL_Renderer* gRenderer;
bool initialize();

void finalize();

SDL_Surface* loadSurface(std::string path);

SDL_Texture* loadTexture(std::string path);

SDL_Renderer* getRenderer();

void exitGame();
void render(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* desrect);

int draw(void* data);
#endif
