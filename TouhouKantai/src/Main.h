#ifndef MAIN_H
#define MAIN_H

#include "Global.h"

#include "MainMenu.h"
#include "BulletFactory.h"
/*
 * Author: Zhang Huayan
 * ID: 6511043
 * Main
 * Main.h/Main.cpp defines the entry of the game and provides several 
 * functions for loading image and drawing.
 * 
 */


bool initialize();
void finalize();
//int draw(void* data);

int kbdListener(void* data);
#endif
