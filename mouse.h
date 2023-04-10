enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_LEFT_DOWN,
};

class BUTTON
{
    private:
        SDL_Point cursorPosition;
        ButtonSprite currentSprite;

    public:
        BUTTON();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event* event);
        SDL_Point processClick();
};

// control mouse's cursor
BUTTON button;

BUTTON::BUTTON() {
    cursorPosition.x = -1;
    cursorPosition.y = -1;
    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void BUTTON::setPosition(int x, int y) {
    cursorPosition.x = x;
    cursorPosition.y = y;
}

void BUTTON::handleEvent(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);

        setPosition(x, y);
        if (event->button.button == SDL_BUTTON_LEFT)
        currentSprite = BUTTON_SPRITE_MOUSE_LEFT_DOWN;
    }
}

SDL_Point BUTTON::processClick()
{
    if(currentSprite==BUTTON_SPRITE_MOUSE_LEFT_DOWN)
    {
        currentSprite=BUTTON_SPRITE_MOUSE_OUT;
        return cursorPosition;
    }
    return {-1,-1};
}
