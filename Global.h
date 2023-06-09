
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
    //draw rectangle
    void DrawRectangle(int x,int y,int w,int h,int r,int g,int b,int a)
    {
        SDL_Rect rect={x,y,w,h};
        SDL_SetRenderDrawColor(g_renderer, r, g, b, a);
        SDL_RenderFillRect(g_renderer, &rect);
    }
    bool inside_Rectangle(int x,int y,SDL_Rect rect)
    {
        if(rect.x<=x && x<=rect.x+rect.w
        && rect.y<=y && y<=rect.y+rect.h) return true;
        return false;
    }
