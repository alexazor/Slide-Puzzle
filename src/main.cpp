#include <cstdlib>
#include "main.h"
#include "check.h"
#include "title.h"

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = nullptr;
    SDL_Renderer *pRenderer = nullptr;
    TTF_Font *pFont = nullptr;

    Mode mode = MODE_TITLE;

    if (init_program(pWindow, pRenderer, pFont) < 0)
        return EXIT_FAILURE;

    switch (mode)
    {
    case MODE_TITLE:
        mode = title(pWindow, pRenderer, pFont);
        break;

    case MODE_GAME:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_SUCCESS;
        break;

    case MODE_QUIT:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_SUCCESS;
        break;

    case MODE_ERROR:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_FAILURE;
        break;

    default:
        SDL_Log("Unknown mode!");
        close_program(pWindow, pRenderer, pFont);
        break;
    }

    return EXIT_FAILURE;
}