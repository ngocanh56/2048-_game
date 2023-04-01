class IMAGE
{
private:
    SDL_Texture* texture;
public:
    IMAGE();
    ~IMAGE();

    bool loadImage(std::string path);
    bool loadText();
    void free();
    void render(int x,int y,int w,int h);
};

IMAGE image;

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
