
#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_
#include<iostream>
#include <windows.h>
#include <SDL.h>
#include <sdl_image.h>
#include <sdl_mixer.h>
#include <sdl_ttf.h>
#include <string>
using namespace std;
static SDL_Window* g_window= NULL;
static SDL_Renderer* g_renderer=NULL;
static SDL_Event g_event;

//Screen
const int screen_width=1920;
const int screen_height=1080;
const int screen_pixel=32;

int X=725, Y=400, SizeCell=127;
SDL_Rect Restart_Rect={X+SizeCell*3-13,264,62,60};
SDL_Rect Cancel_Rect={X+SizeCell*3+52,264,62,62};

bool game_over=false;

Mix_Music *music=NULL;
int number,best;
static TTF_Font* g_Font;
#endif // COMMON_FUNCTION_H_
