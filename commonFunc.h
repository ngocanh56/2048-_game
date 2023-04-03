<<<<<<< HEAD


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
const int screen_width=1280;
const int screen_height=640;
const int screen_pixel=32;

const int color_key_red=167;
const int color_key_green=175;
const int color_key_blue=180;

const int render_draw_color=0xff;
#endif // COMMON_FUNCTION_H_
=======


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
const int screen_width=1280;
const int screen_height=640;
const int screen_pixel=32;

const int color_key_red=167;
const int color_key_green=175;
const int color_key_blue=180;

const int render_draw_color=0xff;
#endif // COMMON_FUNCTION_H_
>>>>>>> fcff905092ba849c91c7deac0adfc83158270abf
