#include "initialisation.h"

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