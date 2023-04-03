#include <bits/stdc++.h>
#include "commonFunc.h"
#include "Global.h"
#include "LoadImage.h"
#include "Board.h"

using namespace std;

int main(int argc,char* argv[])
{
    srand(time(NULL));
    InitData(g_window,g_renderer);

    Board board;
    board.initBoard();
    board.createBoard();

    bool is_quit=false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type==SDL_QUIT) is_quit=true;
            else if (g_event.type==SDL_KEYDOWN)
            {
                switch (g_event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if(board.modifyBoard(UP)==true) board.createCell();
                        break;
                    case SDLK_DOWN:
                        if(board.modifyBoard(DOWN)==true) board.createCell();
                        break;
                    case SDLK_RIGHT:
                        if(board.modifyBoard(RIGHT)==true) board.createCell();
                        break;
                    case SDLK_LEFT:
                        if(board.modifyBoard(LEFT)==true) board.createCell();
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(g_renderer,255,255,255,255);
        SDL_RenderClear(g_renderer);

        board.printBoard();
        board.ModifyIndex();
        if(board.Endgame()) {is_quit=true;SDL_Delay(5000);}

        SDL_Delay(50);
        SDL_RenderPresent(g_renderer);
    }
    return 0;
}
