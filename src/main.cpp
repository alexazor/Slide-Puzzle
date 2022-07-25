#include <cstdlib>
#include "main.h"
#include "check.h"
#include "title.h"

int main(int argc, char *argv[])
{
    SDL_Window *pWindow = nullptr;
    SDL_Renderer *pRenderer = nullptr;
    TTF_Font *pFont = nullptr;

    int puzzleSize = 0;

    State state = STATE_TITLE;

    if (init_program(pWindow, pRenderer, pFont) < 0)
        return EXIT_FAILURE;

    while (true)
    {
        switch (state)
        {
        case STATE_TITLE:
            state = title(pRenderer, pFont, puzzleSize);
            break;

        case STATE_GAME:
            SDL_Log("GAME\n-->%d", puzzleSize);
            SDL_Delay(4000);
            close_program(pWindow, pRenderer, pFont);
            return EXIT_SUCCESS;
            break;

        case STATE_DEMO:
            SDL_Log("DEMO\n-->%d", puzzleSize);
            SDL_Delay(4000);
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
            return EXIT_FAILURE;
            break;
        }
    }
    return EXIT_FAILURE;
}