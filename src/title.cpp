#include "title.h"

Mode title(SDL_Window *pWindow, SDL_Renderer *pRenderer, TTF_Font *pFont)
{
    SDL_Event events;
    Mode mode = MODE_TITLE;

    while (mode == MODE_TITLE)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                mode = MODE_QUIT;
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
        SDL_RenderDrawLine(pRenderer, 17, 22, 504, 478);
        SDL_RenderPresent(pRenderer);
    }

    return mode;
}