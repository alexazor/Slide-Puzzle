#include <cstdlib>
#include "main.h"
#include "check.h"
#include "title.h"

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = nullptr;
    SDL_Renderer *pRenderer = nullptr;
    TTF_Font *pFont = nullptr;

    State state = STATE_TITLE;

    if (init_program(pWindow, pRenderer, pFont) < 0)
        return EXIT_FAILURE;

    switch (state)
    {
    case STATE_TITLE:
        state = title(pRenderer, pFont);
        break;

    case STATE_GAME:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_SUCCESS;
        break;

    case STATE_QUIT:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_SUCCESS;
        break;

    case STATE_ERROR:
        close_program(pWindow, pRenderer, pFont);
        return EXIT_FAILURE;
        break;

    default:
        SDL_Log("Unknown state!");
        close_program(pWindow, pRenderer, pFont);
        break;
    }

    return EXIT_FAILURE;
}