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
    int numTurns = 3;

    while(!is_quit)
    {
        while(SDL_PollEvent(&g_event))
        {
            if(g_event.type==SDL_QUIT) {
                is_quit=true;
                break;
            }

            if(numTurns <= 0 || board.Endgame()) continue;

            if (g_event.type==SDL_KEYDOWN)
            {
                numTurns--;
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

        SDL_SetRenderDrawColor(g_renderer,221,204,235,0);
        SDL_RenderClear(g_renderer);

        if (numTurns <= 0 || board.Endgame()) board.printEndgame();
        else board.printBoard(false);

        SDL_Delay(20);
        SDL_RenderPresent(g_renderer);
    }

    //SDL_Delay(5000);
    return 0;
}
