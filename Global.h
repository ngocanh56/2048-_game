#ifndef BOARDGAME_H
#define BOARDGAME_H
#include "commonFunc.h"
    void Print_Bug(const string& Bug,bool Failed)
    {
        cout<<Bug<<"Name Bug: "<<SDL_GetError()<<'\n';
        if(Failed)
        {
            SDL_Quit();
            exit;
        }
    }
    void InitData(SDL_Window* &g_window, SDL_Renderer*& g_renderer)
    {
        if( SDL_Init (SDL_INIT_EVERYTHING) ) Print_Bug("SDL_Init fail",true);

        g_window=SDL_CreateWindow("2048",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screen_width,screen_height,
                                  SDL_WINDOW_SHOWN);
        if(g_window==NULL) Print_Bug("Create Window fail",true);

        g_renderer=SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED |
                                    SDL_RENDERER_PRESENTVSYNC);
        if(g_renderer==NULL) Print_Bug("Create renderer fail",true);

    }
    //close program
    void close(SDL_Window* g_window, SDL_Renderer* g_renderer)
    {
        SDL_DestroyRenderer(g_renderer);
        SDL_DestroyWindow(g_window);
        SDL_Quit();
    }
#endif // BOARDGAME_H

