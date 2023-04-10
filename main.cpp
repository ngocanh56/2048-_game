#include <bits/stdc++.h>
#include "commonFunc.h"
#include "Global.h"
#include "LoadImage.h"
#include "Board.h"
#include "mouse.h"
using namespace std;
int main(int argc,char* argv[])
{
    srand(time(NULL));
    InitData(g_window,g_renderer);

    TTF_Init();
    g_Font=TTF_OpenFont("Anton-Regular.ttf",  24);

    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);

    Board board;
    board.set_up_Board();

    string name=to_string(rand()%2+1);
    BACKGROUND.loadImage("Display/background"+name+".jpg");
    TITLE.loadImage("Display/TitleBar.jpg");
    bool is_quit=false;

    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event) )
        {

            button.handleEvent(&g_event);
            SDL_Point coor=button.processClick();

            if(inside_Rectangle(coor.x,coor.y,Restart_Rect))
            {
                string name=to_string(rand()%2+1);
                BACKGROUND.loadImage("Display/background"+name+".jpg");
                board.set_up_Board();
            }
            if(inside_Rectangle(coor.x,coor.y,Cancel_Rect)) is_quit=true;

            if(g_event.type==SDL_QUIT)
            {
                is_quit=true;
                break;
            }

            if (!number && g_event.type==SDL_KEYDOWN )
            {
                switch (g_event.key.keysym.sym)
                {
                    case SDLK_UP:
                        board.modifyBoard(UP);
                        break;
                    case SDLK_DOWN:
                        board.modifyBoard(DOWN);
                        break;
                    case SDLK_RIGHT:
                        board.modifyBoard(RIGHT);
                        break;
                    case SDLK_LEFT:
                        board.modifyBoard(LEFT);
                        break;
                }
            }
        }

        if ( board.Endgame())
        {
            number++;
            board.printEndgame();
            if(number<=2)
            {
                    music=Mix_LoadMUS("Sound/Gameover_Sound.wav");
                    Mix_PlayMusic(music,1);
            }
        }
        else board.printBoard(false);
        SDL_RenderPresent(g_renderer);
    }
    return 0;
}
