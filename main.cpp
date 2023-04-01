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
        for(int i=1;i<39;i++)
         {
            stringstream ss;string path;
            ss<<i;ss>>path;
            path = "Image2/9c47f915a66a4e8af82a47b3b7915fc4wNLPvE1QoVhZfga2-" + path + ".png";

            image.loadImage(path);
            image.render(19,19,150,150);
            SDL_Delay(10);
         }
          //image.loadImage("Image/11.png");
            image.render(19,19,150,150);
        SDL_RenderPresent(g_renderer);
    }
    return 0;
}
