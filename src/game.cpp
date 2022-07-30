#include "game.h"

State game(SDL_Renderer *pRenderer, TTF_Font *pFont, int puzzleSize, int bloc_width, int bloc_height, int window_width, int window_height)
{
    State state = STATE_GAME;

    const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;
    SDL_Texture *pNumbersTextures[NUMBER_OF_BLOCS];
    SDL_Rect numbersRects[NUMBER_OF_BLOCS];

    int map[NUMBER_OF_BLOCS];

    shuffle_board(map, puzzleSize);

    if (create_textures_board(pRenderer, pFont, pNumbersTextures, puzzleSize) < 0)
        return STATE_ERROR;

    if (create_rectangles_board(pNumbersTextures, numbersRects, puzzleSize, bloc_width, bloc_height) < 0)
    {
        destroy_textures_board(pNumbersTextures, puzzleSize);
        return STATE_ERROR;
    }

    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

    return event_loop_game(pRenderer, pNumbersTextures, numbersRects, puzzleSize, map, bloc_width, bloc_height, window_width, window_height);
}

State event_loop_game(SDL_Renderer *pRenderer,
                      SDL_Texture *pNumbersTextures[],
                      SDL_Rect numbersRects[],
                      int puzzleSize,
                      int map[],
                      int bloc_width,
                      int bloc_height,
                      int window_width,
                      int window_height)
{
    SDL_Event events;
    State state = STATE_GAME;

    const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

    SDL_Rect blocRect = SDL_Rect{0, 0, bloc_width, bloc_height};

    int size;

    while (state == STATE_GAME)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                state = STATE_TITLE;
                break;

                // case SDL_MOUSEBUTTONDOWN:
                //     if (events.button.button == SDL_BUTTON_LEFT)
                //     break;

                // case SDL_MOUSEMOTION:
                //     selectedSizeIndex = -1;
                //     for (sizeIndex = 0; sizeIndex < PUZZLE_SIZES; sizeIndex++)
                //         if (mouse_over_rectangle(puzzleSizesRects[sizeIndex], events.motion.x, events.motion.y))
                //             selectedSizeIndex = sizeIndex;
                //     break;

            default:
                break;
            }
        }

        if (update_screen_board(pRenderer, pNumbersTextures, numbersRects, &blocRect, NUMBER_OF_BLOCS, puzzleSize, map, bloc_width, bloc_height) < 0)
            state = STATE_ERROR;
    }

    destroy_textures_board(pNumbersTextures, puzzleSize);
    return state;
}
