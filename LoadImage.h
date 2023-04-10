#include "commonFunc.h"
class IMAGE
{
private:
    SDL_Texture* texture;
public:
    IMAGE();
    ~IMAGE();

    bool loadImage(std::string path);
    void loadText(string text,SDL_Color color);
    void free();
    void render(int x,int y,int w,int h);
};

IMAGE image;
IMAGE BACKGROUND;
IMAGE TITLE;
IMAGE::IMAGE()
{
    texture=NULL;
}
IMAGE::~IMAGE()
{
    free();
}
bool IMAGE::loadImage(std::string path)
{
    free();
    SDL_Surface *surface=IMG_Load(path.c_str());
    texture=SDL_CreateTextureFromSurface(g_renderer,surface);

    SDL_FreeSurface(surface);
}
void IMAGE::free()
{
    if(texture!=NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}
void IMAGE::render(int x,int y,int w,int h)
{
    SDL_Rect rect={x,y,w,h};
    SDL_RenderCopy(g_renderer,texture,NULL,&rect);
}
void IMAGE::loadText(string text,SDL_Color color)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Blended(g_Font,text.c_str(),color);
    texture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
    SDL_FreeSurface(textSurface);
}
