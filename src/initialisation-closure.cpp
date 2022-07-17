#include "initialisation-closure.h"

void error_message()
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
}

int init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        error_message();
        return -1;
    }
    else
        return 0;
}

int init_TTF()
{
    if (TTF_Init() < 0)
    {
        SDL_Quit();
        error_message();
        return -1;
    }
    else
        return 0;
}

int create_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer)
{
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_Quit();
        TTF_Quit();
        return -1;
    }
    else
    {
        SDL_SetWindowTitle(pWindow, "Slide-Puzzle");
        return 0;
    }
}

int init_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer)
{
    if (init_SDL() < 0 || init_TTF() < 0 || create_window(pWindow, pRenderer) < 0)
        return -1;
    else
        return 0;
}

void close_program(SDL_Window *&pWindow, SDL_Renderer *&pRenderer)
{
    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    TTF_Quit();
    SDL_Quit();
}

int open_font(TTF_Font *&pFont, char *filePath, int ptSize)
{
    pFont = TTF_OpenFont(filePath, ptSize);

    if (pFont == nullptr)
    {
        error_message();
        return -1;
    }
    else
        return 0;
}

int create_text_surface(SDL_Surface *&textSurface, TTF_Font *font, char *text, SDL_Colour fgColour, TTF_Text_Type textType)
{
    return create_text_surface(textSurface, font, text, fgColour, SDL_Colour{0, 0, 0, 255}, textType);
}

int create_text_surface(SDL_Surface *&textSurface, TTF_Font *font, char *text, SDL_Colour fgColour, SDL_Colour bgColour, TTF_Text_Type textType)
{
    switch (textType)
    {
    case TTF_SOLID:
        textSurface = TTF_RenderText_Solid(font, text, fgColour);
        break;
    case TTF_SHADED:
        textSurface = TTF_RenderText_Shaded(font, text, fgColour, bgColour);
        break;
    case TTF_BLENDED:
        textSurface = TTF_RenderText_Blended(font, text, fgColour);
        break;

    default:
        textSurface = nullptr;
        SDL_Log("Unknown value for textType!");
        break;
    }

    if (textSurface == nullptr)
    {
        error_message();
        return -1;
    }
    else
        return 0;
}
