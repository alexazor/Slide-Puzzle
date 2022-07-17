#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "initialisation-closure.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = nullptr;
    SDL_Renderer *pRenderer = nullptr;
    Mode mode = MODE_TITLE;

    if (init_program(pWindow, pRenderer) < 0)
        return EXIT_FAILURE;

    switch (mode)
    {
    case MODE_TITLE:
        close_program(pWindow, pRenderer);
        return EXIT_SUCCESS;
        break;

    case MODE_GAME:
        close_program(pWindow, pRenderer);
        return EXIT_SUCCESS;
        break;

    case MODE_QUIT:
        close_program(pWindow, pRenderer);
        return EXIT_SUCCESS;
        break;

    case MODE_ERROR:
        close_program(pWindow, pRenderer);
        return EXIT_FAILURE;
        break;

    default:
        SDL_Log("Unknown mode!");
        close_program(pWindow, pRenderer);
        return EXIT_FAILURE;
        break;
    }
}