#include "title.h"

Mode chose_mode(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, Mode mode)
{
    SDL_Event events;

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
    }

    return mode;
}
// 10 11 18 19 20 13
void update_title_window(SDL_Window *&pWindow, SDL_Renderer *&pRenderer, TTF_Font *titleFont, TTF_Font *textFont)
{
    // SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    // SDL_RenderClear(pRenderer);
    // SDL_SetRenderDrawColor(pRenderer, 124, 75, 97, 255);
    // SDL_RenderDrawLine(pRenderer, 17, 22, 504, 478);
    // SDL_RenderPresent(pRenderer);
}
