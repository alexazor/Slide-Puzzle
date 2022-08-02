#include "game.h"

State game(SDL_Renderer *pRenderer, TTF_Font *pFont, int puzzleSize, int block_width, int block_height, int window_width, int window_height)
{
    State state = STATE_GAME;

    const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

    SDL_Texture *pNumbersTextures[NUMBER_OF_BLOCS];
    SDL_Rect numbersRects[NUMBER_OF_BLOCS];

    int map[NUMBER_OF_BLOCS];

    if (create_textures_board(pRenderer, pFont, pNumbersTextures, puzzleSize) < 0)
        return STATE_ERROR;

    if (create_rectangles_board(pNumbersTextures, numbersRects, puzzleSize, block_width, block_height) < 0)
    {
        destroy_textures_board(pNumbersTextures, puzzleSize);
        return STATE_ERROR;
    }

    shuffle_board(map, puzzleSize, numbersRects, block_width, block_height);

    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND);

    return event_loop_game(pRenderer, pNumbersTextures, numbersRects, puzzleSize, map, block_width, block_height, window_width, window_height);
}

State event_loop_game(SDL_Renderer *pRenderer,
                      SDL_Texture *pNumbersTextures[],
                      SDL_Rect numbersRects[],
                      int puzzleSize,
                      int map[],
                      int block_width,
                      int block_height,
                      int window_width,
                      int window_height)
{
    SDL_Event events;
    State state = STATE_GAME;

    const int NUMBER_OF_BLOCS = puzzleSize * puzzleSize;

    SDL_Rect blockRect = SDL_Rect{0, 0, block_width, block_height};

    int size, iClick, jClick, iVoid, jVoid;

    find_void(map, puzzleSize, iVoid, jVoid);

    while (state == STATE_GAME)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                state = STATE_TITLE;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (events.button.button == SDL_BUTTON_LEFT)
                {
                    get_block_position(events.button.x, events.button.y, block_height, block_width, iClick, jClick);
                    move_line(map, puzzleSize, iClick, jClick, iVoid, jVoid, numbersRects, block_width, block_height);
                }
                break;

            default:
                break;
            }
        }

        if (update_screen_board(pRenderer, pNumbersTextures, numbersRects, &blockRect, puzzleSize, map, block_width, block_height) < 0)
            state = STATE_ERROR;
    }

    destroy_textures_board(pNumbersTextures, puzzleSize);
    return state;
}
